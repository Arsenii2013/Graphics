#ifndef COLORPOSCUBE_H
#define COLORPOSCUBE_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include <QColor>
#include <vector>
#include <random>
#include <algorithm>

#include "side.h"

class ColorPosCube
{
    std::vector<CubeSide> sides;

public:
    ColorPosCube(QVector3D center, GLfloat side, int pointsPerSide, GLenum primitive);

    enum class Side{
        FRONT,
        BACK,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    void setColor(Side side, GLfloat r, GLfloat g, GLfloat b);

    void setColor(Side side, QColor color);

    void setColor(Side side, QColor up_left, QColor up_right, QColor down_left, QColor down_right);

    void setColor(GLfloat r, GLfloat g, GLfloat b);

    void draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions* window);
};

#endif // COLORPOSCUBE_H
