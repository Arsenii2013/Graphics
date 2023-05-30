#ifndef SETTINGS_H
#define SETTINGS_H

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QVector4D>
#include <QSlider>
#include <iostream>

#include "selectcolor.h"

class Settings : public QWidget
{
    Q_OBJECT
    QComboBox *shader;
    std::string active_shader{"Directional"};

    SelectColorButton *Ca;
    QLabel Ca_label{"Ca", this};
    QVector4D ca{0,   0,    0.2, 1};

    SelectColorButton *Cd;
    QLabel Cd_label{"Cd", this};
    QVector4D cd{0.5, 0.5,  1, 1};

    SelectColorButton *Cs;
    QLabel Cs_label{"Cs", this};
    QVector4D cs{1,   1,    1, 1};

    SelectColorButton *Ga;
    QLabel Ga_label{"Ga", this};
    QVector4D ga{0.1, 0.1,  0.1, 1};

    SelectColorButton *Ld;
    QLabel Ld_label{"Ld", this};
    QVector4D ld{1,   1,    1, 1};

    SelectColorButton *Ls;
    QLabel Ls_label{"Ls", this};
    QVector4D ls{1,   1,    1, 1};

    QSlider *x;
    QLabel x_label{"x", this};
    QSlider *y;
    QLabel y_label{"y", this};
    QSlider *z;
    QLabel z_label{"z", this};
    QVector4D point_pos{1,   1,    1, 1};

    QSlider *edge;
    QLabel edge_label{"edge", this};
    int Edge = 5;
public:
    explicit Settings(QWidget *parent = nullptr);

    std::string getShader(){
        return active_shader;
    }

    QVector4D getCa(){
        return ca;
    }
    QVector4D getCd(){
        return cd;
    }
    QVector4D getCs(){
        return cs;
    }
    QVector4D getGa(){
        return ga;
    }
    QVector4D getLd(){
        return ld;
    }
    QVector4D getLs(){
        return ls;
    }
    QVector4D getPoint(){
        return point_pos;
    }
    int getEdge(){
        return Edge;
    }
private slots:
    void _x(int x){
        point_pos.setX(x/100.);
    }
    void _y(int y){
        point_pos.setY(y/100.);
    }
    void _z(int z){
        point_pos.setZ(z/100.);
    }
    void _shaderChanged(const QString &name){
        active_shader = name.toStdString();
    }

    void _CaChanged(const QColor &color){
        ca.setX(color.redF());
        ca.setY(color.greenF());
        ca.setZ(color.blueF());
        ca.setW(color.alphaF());
    }

    void _CdChanged(const QColor &color){
        cd.setX(color.redF());
        cd.setY(color.greenF());
        cd.setZ(color.blueF());
        cd.setW(color.alphaF());
    }

    void _CsChanged(const QColor &color){
        cs.setX(color.redF());
        cs.setY(color.greenF());
        cs.setZ(color.blueF());
        cs.setW(color.alphaF());
    }

    void _GaChanged(const QColor &color){
        ga.setX(color.redF());
        ga.setY(color.greenF());
        ga.setZ(color.blueF());
        ga.setW(color.alphaF());
    }

    void _LdChanged(const QColor &color){
        ld.setX(color.redF());
        ld.setY(color.greenF());
        ld.setZ(color.blueF());
        ld.setW(color.alphaF());
    }

    void _LsChanged(const QColor &color){
        ls.setX(color.redF());
        ls.setY(color.greenF());
        ls.setZ(color.blueF());
        ls.setW(color.alphaF());
    }

    void _EdgeChanged(int edge){
        Edge = edge;
    }
};

#endif // SETTINGS_H
