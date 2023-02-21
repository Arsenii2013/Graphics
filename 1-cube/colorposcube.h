#ifndef COLORPOSCUBE_H
#define COLORPOSCUBE_H

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include <QColor>
#include <vector>

class ColorPosCube
{
    GLfloat *points = nullptr;
    GLfloat *colors = nullptr;
    GLenum primitive;
public:
    ColorPosCube(QVector3D center, GLfloat side, GLenum primitive);

    enum class Side{
        FRONT,
        BACK,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    void setColor(Side side, GLfloat r, GLfloat g, GLfloat b){

    }

    void setColor(Side side, QColor color){

    }

    void setColor(Side side, QColor up_left, QColor up_right, QColor down_left, QColor down_right){

    }

    const GLfloat *getPoints(){
        return points;
    }

    const GLfloat *getColors(){
        return colors;
    }

    GLenum getPrimitive(){
        return primitive;
    }

    int getPointsCnt();

    ~ColorPosCube(){
        delete [] points;
        delete [] colors;
    }
};

#endif // COLORPOSCUBE_H
