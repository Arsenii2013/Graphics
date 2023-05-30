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
#include <QOpenGLTexture>

#include <iostream>

#include <random>

//! [1]
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

    ShaderWrapper directonal;
    //ShaderWrapper point;
    //ShaderWrapper spot;

    Settings settings;

    Camera cam{};

    /*std::vector<GraphicObj> cubes{{{0., 0., -5.}, 10, 100, GraphicObj::Type::CUBE},
                                    {{0., -5., 0.}, 10, 100, GraphicObj::Type::CUBE},
                                    {{0., 5., 0.}, 10, 100, GraphicObj::Type::CUBE},
                                    {{0., 0., 5.}, 10, 100, GraphicObj::Type::CUBE},
                                    {{5., 0., 0.}, 10, 100, GraphicObj::Type::CUBE},
                                    {{-5., 0., 0.}, 10, 100, GraphicObj::Type::CUBE}};*/
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
    directonal = ShaderWrapper{"../6-texture/shaders/directional.vsh", "../6-texture/shaders/frag.fsh", this};
    //point = ShaderWrapper{"../6-texture/shaders/point.vsh", "../6-texture/shaders/frag.fsh", this};
    //spot = ShaderWrapper{"../6-texture/shaders/spot.vsh", "../6-texture/shaders/frag.fsh", this};
}
//! [4]

//! [5]
void CubeWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    std::vector<GraphicObj> cubes{{{0., 0., -4.}, 4, settings.getEdge(), GraphicObj::Type::BALL}};
    for(auto& cube: cubes){
        cube.selfRotate(30.f * m_frame / screen()->refreshRate(), QVector3D{0., 1., 0.});
    }

    ShaderWrapper* active = 0;
    if(settings.getShader() == "Directional"){
        active = &directonal;
    }else if(settings.getShader() == "Point"){
        active = &directonal;
        //active = &point;
    }else if(settings.getShader() == "Spot"){
        active = &directonal;
        //active = &spot;
    }

    if(active){
        active->setActive();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);

        QImage image("../6-texture/Earth_Albedo.jpg");
        image = image.convertToFormat(QImage::Format_ARGB32);
        QOpenGLTexture tex(image);
        tex.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        tex.setWrapMode(QOpenGLTexture::Repeat);
        tex.create();

        // given some `width`, `height` and `data_ptr`
        tex.setSize(1, 1, 1);
        tex.setFormat(QOpenGLTexture::RGBA8_UNorm);
        tex.allocateStorage();
        tex.bind(0);
        active->m_program->setUniformValue("tex", 0);

        QImage image1("../6-texture/Earth_NormalMap.jpg");
        image1 = image1.convertToFormat(QImage::Format_ARGB32);
        QOpenGLTexture norm(image1);
        norm.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        norm.setWrapMode(QOpenGLTexture::Repeat);
        norm.create();

        // given some `width`, `height` and `data_ptr`
        norm.setSize(1, 1, 1);
        norm.setFormat(QOpenGLTexture::RGBA8_UNorm);
        norm.allocateStorage();
        norm.bind(1);
        active->m_program->setUniformValue("norm", 1);

        //active->set("tex", image.m_texture);

        active->set("Ga", settings.getGa());
        active->set("Ld", settings.getLd());
        active->set("Ls", settings.getLs());
        active->set("view_point", cam.getPosition());

        if(settings.getShader() == "Directional"){
            active->set("light_direction", QVector4D(1., 1., 0., 1.));
        }else if(settings.getShader() == "Point"){
            active->set("light_point", settings.getPoint());
        }else if(settings.getShader() == "Spot"){
            active->set("light_direction", QVector4D(0., 0., 1., 1.));
            active->set("light_point", QVector4D(0., 0., 1., 1.));
        }

        active->set("view", cam.getViewMatrix());

        for(auto& cube: cubes){
            active->set("model", cube.getModelMatrix());
            active->set("model_TI", cube.getModelMatrix().transposed().inverted());
            cube.draw(active->getLocation("posAttr"), active->getLocation("norAttr"), this);
        }

        //std::cout << TransferObject::getInstance().getShader() << std::endl;

        active->deactivate();
    }

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
