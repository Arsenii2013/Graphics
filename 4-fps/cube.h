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
#include <memory>

#include "side.h"

class GraphicObj
{
    std::shared_ptr<std::vector<CubeSide>> sides;

    QMatrix4x4 mScale;
    QMatrix4x4 mRotation;
    QMatrix4x4 mTranslation;
    QMatrix4x4 mAdditional;
    QMatrix4x4 cache;
    bool cached = false;
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
        cached = false;
        mScale.scale(scale);
    }

    void selfRotate(float angle, QVector3D axis){
        cached = false;
        mRotation.rotate(angle, axis);
    }

    void selfTranslate(QVector3D delta){
        cached = false;
        mTranslation.translate(delta);
    }

    QMatrix4x4 getModelMatrix(){
        if(!cached){
            cache = mAdditional * mTranslation * mRotation * mScale;
            cached = true;
        }
        return cache;
    }
};

#endif // COLORPOSCUBE_H
