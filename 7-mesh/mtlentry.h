#ifndef MTLENTRY_H
#define MTLENTRY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVector3D>
#include <QtGui/QOpenGLFunctions>
#include <iostream>
#include <string>


struct MTLEntry
{
    std::string name{};
    QVector3D Ka{1., 1., 1.};
    QVector3D Kd{1., 1., 1.};
    QVector3D Ks{1., 1., 1.};
    GLfloat Ns{20.};
    GLfloat d{1.};
};

std::istream& operator>> (std::istream& is, QVector3D& v);
std::istream& operator>> (std::istream& is, MTLEntry& e);

#endif // MTLENTRY_H
