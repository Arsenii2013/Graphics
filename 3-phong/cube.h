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

class GraphicObj
{
    std::vector<CubeSide> sides;

    QMatrix4x4 mScale;
    QMatrix4x4 mRotation;
    QMatrix4x4 mTranslation;
    QMatrix4x4 mAdditional;
public:
    enum class Type{
        CUBE,
        BALL,
    };

    GraphicObj(QVector3D center, GLfloat side, int pointsPerSide, Type type);

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

    void selfScale(QVector3D scale){
        mScale.scale(scale);
    }

    void selfRotate(float angle, QVector3D axis){
        mRotation.rotate(angle, axis);
    }

    void selfTranslate(QVector3D delta){
        mTranslation.translate(delta);
    }

    QMatrix4x4 getModelMatrix(){
        return mAdditional * mTranslation * mRotation * mScale;
    }
};

#endif // COLORPOSCUBE_H