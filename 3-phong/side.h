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

class CubeSide
{
    std::vector<Strip> strips;

    constexpr int getStripSize(int pointsPerSide);
public:

    CubeSide(int pointsPerSide, QMatrix4x4 transform, std::function<GLfloat (GLfloat, GLfloat)> z_gen,
                                                      std::function<QVector4D (GLfloat, GLfloat)> normal_gen,
                                                      std::function<QVector4D (GLfloat, GLfloat)> color_gen);
    CubeSide(int pointsPerSide, QMatrix4x4 transform, std::string type);


    void draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window);
};

#endif // SIDE_H
