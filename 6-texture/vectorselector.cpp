#include "vectorselector.h"

VectorSelector::VectorSelector(QWidget *parent)
    : QWidget{parent}
{
    xSlider = new QSlider(Qt::Horizontal, this);
    xSlider->setMaximum(1);
    xSlider->setMaximum(-1);
    xSlider->move(0, 0);
    xSlider->show();

    ySlider = new QSlider(Qt::Horizontal, this);
    ySlider->setMaximum(1);
    ySlider->setMaximum(-1);
    ySlider->move(0, 10);
    ySlider->show();

    zSlider = new QSlider(Qt::Horizontal, this);
    zSlider->setMaximum(1);
    zSlider->setMaximum(-1);
    zSlider->move(0, 20);
    zSlider->show();

   // QObject::connect(shader, SIGNAL(currentTextChanged(const QString &)),
     //                this,   SLOT(_shaderChanged(const QString &)));
}
