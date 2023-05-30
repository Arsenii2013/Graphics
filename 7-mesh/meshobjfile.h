#ifndef MESHOBJFILE_H
#define MESHOBJFILE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMatrix4x4>
#include <QtGui/QOpenGLFunctions>


class MeshObjFile
{
    QMatrix4x4 mScale;
    QMatrix4x4 mRotation;
    QMatrix4x4 mTranslation;
    QMatrix4x4 mAdditional;
public:
    void load(const std::string& f_name);

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

#endif // MESHOBJFILE_H
