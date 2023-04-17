#include "mainwindow.h"
#include "cube.h"
#include "camera.h"
#include "settings.h"
#include "shaderwrapper.h"
#include "transferobject.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

#include <QWidget>
#include <QApplication>
#include <QColorDialog>
#include <QEvent>
#include <QKeyEvent>

#include <iostream>

#include <random>
#include <chrono>

//! [1]
//!

std::vector<GraphicObj> genCubes(int cnt_per_side, int points_per_side){
    std::vector<GraphicObj> cubes{};
    for(int i = -cnt_per_side/2; i < cnt_per_side/2; i++){
        for(int j = -cnt_per_side/2; j < cnt_per_side/2; j++){
            cubes.emplace_back(QVector3D{i, -2., j}, 1.3, points_per_side, GraphicObj::Type::CUBE);
        }
    }
    return cubes;
}

class CubeWindow : public OpenGLWindow
{
public:
    CubeWindow();

    void initialize() override;
    void render() override;
protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;
private:
    int m_frame;

    ShaderWrapper point;

    Settings settings;

    Camera cam{};

    std::vector<GraphicObj> cubes = genCubes(1, 1);
    int prevPointsPerSide = 1;
};

CubeWindow::CubeWindow()
        :  m_frame(0)
{
}
//! [1]

//! [2]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget widget;
    //QColor color = QColorDialog::getColor(Qt::yellow, &widget);
    //TransferObj::getInstance().setColor(color);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    CubeWindow window;
    window.setFormat(format);
    window.resize(1920, 1080);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
//! [2]


//! [3]

//! [3]

//! [4]
void CubeWindow::initialize()
{
    point = ShaderWrapper{"../4-fps/shaders/point.vsh", "../4-fps/shaders/frag.fsh", this};
}
//! [4]

//! [5]
void CubeWindow::render()
{
    settings.frame();
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    if(settings.getEdge() != prevPointsPerSide || settings.getCubes() * settings.getCubes() != cubes.size()){
        prevPointsPerSide = settings.getEdge();
        cubes = genCubes(settings.getCubes(), prevPointsPerSide);
    }

    //for(auto& cube: cubes){
        //cube.selfRotate(1.f *m_frame / screen()->refreshRate(), QVector3D{0., 1., 0.});
    //}

    point.setActive();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    point.set("Ca", settings.getCa());
    point.set("Cd", settings.getCd());
    point.set("Cs", settings.getCs());
    point.set("Ga", settings.getGa());
    point.set("Ld", settings.getLd());
    point.set("Ls", settings.getLs());
    point.set("view_point", cam.getPosition());

    auto now = std::chrono::steady_clock::now();
    static auto prev = now;
    static double elapsed = 0;

    elapsed += std::chrono::duration<double>(now - prev).count();
    if(elapsed > 2.d){
        elapsed -= 2.d;
    }
    double pi = atan(1)*4;
    double sin = std::sin(pi * elapsed);
    double cos = std::cos(pi * elapsed);
    point.set("lights_cnt", settings.getLightsCnt());
    for(int i = 0; i < settings.getLightsCnt(); i++){
        point.set("light_points[" + std::to_string(i) + "]", QVector4D(double(i) * sin, 1, double(i) * cos, 1.));
    }

    prev = now;
    point.set("view", cam.getViewMatrix());

    GLuint posA = point.getLocation("posAttr");
    GLuint norA = point.getLocation("norAttr");

    for(auto& cube: cubes){
        point.set("model", cube.getModelMatrix());
        cube.draw(posA, norA, this);
    }

    //std::cout << TransferObject::getInstance().getShader() << std::endl;

    point.deactivate();

    ++m_frame;
}

bool CubeWindow::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::KeyPress:
            {
            QKeyEvent *ke = static_cast<QKeyEvent *>(event);
            switch (ke->key()) {
                case Qt::Key_W:
                cam.Translate(QVector3D{0., 0., 0.1});
                break;
                case Qt::Key_S:
                cam.Translate(QVector3D{0., 0., -0.1});
                break;
                case Qt::Key_A:
                cam.Translate(QVector3D{0.1, 0., 0.});
                break;
                case Qt::Key_D:
                cam.Translate(QVector3D{-0.1, 0., 0.});
                break;
                case Qt::Key_Shift:
                cam.Translate(QVector3D{0., -0.1, 0.});
                break;
                case Qt::Key_Control:
                cam.Translate(QVector3D{0., 0.1, 0.});
                break;
                case Qt::Key_Up:
                cam.selfRotate(1, QVector3D{1., 0., 0.});
                break;
                case Qt::Key_Down:
                cam.selfRotate(-1, QVector3D{1., 0., 0.});
                break;
                case Qt::Key_Left:
                cam.selfRotate(1, QVector3D{0., 1., 0.});
                break;
                case Qt::Key_Right:
                cam.selfRotate(-1, QVector3D{0., 1., 0.});
                break;
                default:
                break;
            }
            return true;
            }
        default:
            return OpenGLWindow::event(event);
    }
}

void CubeWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    OpenGLWindow::exposeEvent(event);
}
//! [5]
