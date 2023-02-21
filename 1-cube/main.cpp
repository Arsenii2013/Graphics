#include "mainwindow.h"
#include "colorposcube.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

#include <QWidget>
#include <QApplication>
#include <QColorDialog>

#include <iostream>

//! [1]
class CubeWindow : public OpenGLWindow
{
public:
    CubeWindow();

    void initialize() override;
    void render() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    ColorPosCube cube1{{0., 0., 0.}, 1, GL_TRIANGLE_STRIP};
    ColorPosCube cube2{{1., 0., 0.}, 1, GL_TRIANGLES};
};

CubeWindow::CubeWindow()
        : m_program(0)
        , m_frame(0)
{
}
//! [1]

//! [2]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    CubeWindow window;
    window.setFormat(format);
    window.resize(1920, 1080);
    window.show();

    window.setAnimating(true);

    QWidget widget;
    QColor color = QColorDialog::getColor(Qt::yellow, &widget);

    return app.exec();
}
//! [2]


//! [3]
static const char *vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

static const char *fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";
//! [3]

//! [4]
void CubeWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}
//! [4]

//! [5]
void CubeWindow::render()
{

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    //matrix.perspective(90.0f, 16.f/9.0f, 0.1f, 100.0f);
    //matrix.translate(0, 0, -4);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 1, 0, 0);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    m_program->setUniformValue(m_matrixUniform, matrix);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, cube1.getPoints());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, cube1.getColors());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //glFrontFace(GL_TRUE);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glDrawArrays(cube1.getPrimitive(), 0, cube1.getPointsCnt());

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}
//! [5]
