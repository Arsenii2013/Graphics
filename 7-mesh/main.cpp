#include "mainwindow.h"
#include "camera.h"
#include "settings.h"
#include "shaderwrapper.h"
#include "objstorage.h"

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
#include <filesystem>
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
    Settings settings;
    Camera cam{};
};

CubeWindow::CubeWindow()
    :  m_frame(0)
{
}
//! [1]

//! [2]
int main(int argc, char **argv)
{
    std::filesystem::current_path("/home/sescer/QtCreatorProjects/7-mesh"); //setting path
    //OBJStorage::getInstance().parse("MeshSphere.obj");
    OBJStorage::getInstance().parse("MeshHouse.obj");
    //OBJStorage::getInstance().parse("CraneoOBJ.obj");

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
    directonal = ShaderWrapper{"shaders/directional.vsh", "shaders/frag.fsh", this};
}
//! [4]

//! [5]
void CubeWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    directonal.setActive();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    directonal.set("Ca", settings.getCa());
    directonal.set("Cd", settings.getCd());
    directonal.set("Cs", settings.getCs());
    directonal.set("Ga", settings.getGa());
    directonal.set("Ld", settings.getLd());
    directonal.set("Ls", settings.getLs());
    directonal.set("view_point", cam.getPosition());

    if(settings.getShader() == "Directional"){
        directonal.set("light_direction", QVector4D(0., 0., -1., 1.));
    }else if(settings.getShader() == "Point"){
        directonal.set("light_point", settings.getPoint());
    }else if(settings.getShader() == "Spot"){
        directonal.set("light_direction", QVector4D(0., 0., 1., 1.));
        directonal.set("light_point", QVector4D(0., 0., 1., 1.));
    }

    directonal.set("view", cam.getViewMatrix());

    directonal.set("model", QMatrix4x4());
    //OBJStorage::getInstance().get("Sphere[-403266]").draw(directonal.getLocation("posAttr"), directonal.getLocation("norAttr"), -1, this);
    OBJStorage::getInstance().get("House022[-45008]").draw(directonal.getLocation("posAttr"), directonal.getLocation("norAttr"), -1, this);
    //OBJStorage::getInstance().get("Dientes").draw(directonal.getLocation("posAttr"), directonal.getLocation("norAttr"), -1, this);
    directonal.deactivate();

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
