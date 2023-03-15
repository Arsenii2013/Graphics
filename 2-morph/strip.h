#ifndef STRIP_H
#define STRIP_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include <QColor>
#include <vector>
#include <random>
#include <algorithm>


class Strip{
    GLfloat *points = nullptr;
    GLfloat *colors = nullptr;
    int pointsCnt = 0;
    void Construct(std::vector<GLfloat> pts, std::vector<GLfloat> cls={});
public:
    Strip(std::vector<GLfloat> pts, std::vector<GLfloat> cls={});

    Strip(std::vector<QVector4D> pts, std::vector<QVector4D> cls={});

    ~Strip();

    void fillRandom();

    void draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window);
};

#endif // STRIP_H
