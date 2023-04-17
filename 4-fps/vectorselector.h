#ifndef VECTORSELECTOR_H
#define VECTORSELECTOR_H

#include <QWidget>
#include <QSlider>

class VectorSelector : public QWidget
{
    Q_OBJECT
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
public:
    explicit VectorSelector(QWidget *parent = nullptr);

signals:
    void valueChanged(int value);
};

#endif // VECTORSELECTOR_H
