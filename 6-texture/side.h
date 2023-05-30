#ifndef SIDE_H
#define SIDE_H
#include "strip.h"

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include <QColor>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <optional>

class CubeSide
{
    std::vector<Strip> strips;

    constexpr int getStripSize(int pointsPerSide);

    void genCube(int pointsPerSide, QMatrix4x4 transform);
    void genBall(int pointsPerSide, QMatrix4x4 transform);
public:
    enum class Type{
        BALL,
        CUBE,
    };

    CubeSide(int pointsPerSide, QMatrix4x4 transform, CubeSide::Type type);


    void draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window);
};

#endif // SIDE_H
