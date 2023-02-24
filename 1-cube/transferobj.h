#ifndef TRANSFEROBJ_H
#define TRANSFEROBJ_H

#include <QColor>
#include <QtGui/QMatrix4x4>
#include <QPoint>
#include "colorposcube.h"

class TransferObj
{
    TransferObj();
    QColor color;
    //ColorPosCube::Side side;
    //QVector axis;

public:
    static TransferObj& getInstance()
    {
        static TransferObj    instance;
        return instance;
    }
    TransferObj(TransferObj const&)     = delete;
    void operator=(TransferObj const&)  = delete;

    void setColor(QColor _color){
        color = _color;
    }

    QColor getColor(){
        return color;
    }
};

#endif // TRANSFEROBJ_H
