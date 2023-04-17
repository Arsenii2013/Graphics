#ifndef CAMERA_H
#define CAMERA_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include <QColor>
#include <vector>
#include <random>
#include <algorithm>

class Camera
{
    QMatrix4x4 mScale;
    QMatrix4x4 mRotation;
    QMatrix4x4 mTranslation;
    QMatrix4x4 mAdditional;
public:
    Camera();

    void selfScale(QVector3D scale){
        mScale.scale(scale);
    }

    void selfRotate(float angle, QVector3D axis){
        mRotation.rotate(angle, axis);
    }

    void Rotate(float angle, QVector3D axis){
        mAdditional.rotate(angle, axis);
    }

    void selfTranslate(QVector3D delta){
        mTranslation.translate(delta);
    }

    void Translate(QVector3D delta){
        mAdditional.translate(delta);
    }

    QMatrix4x4 getViewMatrix(){
        return mAdditional * mTranslation * mRotation * mScale;
    }

    QVector4D getPosition(){
        return getViewMatrix().inverted() * QVector4D(0., 0., 0., 1.);
    }

    QVector4D getViewVector(){
        return getViewMatrix().inverted() * QVector4D(0., 0., 1., 1.);
    }
};

#endif // CAMERA_H
