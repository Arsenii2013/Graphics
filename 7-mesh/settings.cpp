#include "settings.h"

Settings::Settings(QWidget *parent)
    : QWidget{parent}
{
    this->resize(320, 240);
    this->setWindowTitle
          (QApplication::translate("Settings", "Settings"));
    this->show();

    shader = new QComboBox(this);
    shader->addItem("None");
    shader->addItem("Directional");
    shader->addItem("Point");
    shader->addItem("Spot");
    shader->move(100, 100);
    shader->show();

    QObject::connect(shader, SIGNAL(currentTextChanged(const QString &)),
                     this,   SLOT(_shaderChanged(const QString &)));


    Ca = new SelectColorButton(this);
    Ca->move(0, 20);
    Ca->show();
    Ca_label.move(0, 0);
    QObject::connect(Ca, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_CaChanged(const QColor &)));

    Cd = new SelectColorButton(this);
    Cd->move(100, 20);
    Cd->show();
    Cd_label.move(100, 0);
    QObject::connect(Cd, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_CdChanged(const QColor &)));

    Cs = new SelectColorButton(this);
    Cs->move(200, 20);
    Cs->show();
    Cs_label.move(200, 0);
    QObject::connect(Cs, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_CsChanged(const QColor &)));

    Ga = new SelectColorButton(this);
    Ga->move(300, 20);
    Ga->show();
    Ga_label.move(300, 0);
    QObject::connect(Ga, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_GaChanged(const QColor &)));

    Ld = new SelectColorButton(this);
    Ld->move(400, 20);
    Ld->show();
    Ld_label.move(400, 0);
    QObject::connect(Ld, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_LdChanged(const QColor &)));

    Ls = new SelectColorButton(this);
    Ls->move(500, 20);
    Ls->show();
    Ls_label.move(500, 0);
    QObject::connect(Ls, SIGNAL(colorChanged(const QColor &)),
                     this,   SLOT(_LsChanged(const QColor &)));



    x = new QSlider(this);
    x->setMaximum(400);
    x->setMinimum(-400);
    x->move(0, 220);
    x->setGeometry({0, 200, 20, 100});
    x->show();
    x_label.move(0, 200);

    y = new QSlider(this);
    y->setMaximum(400);
    y->setMinimum(-400);
    y->move(100, 220);
    y->setGeometry({100, 200, 20, 100});
    y->show();
    y_label.move(100, 200);

    z = new QSlider(this);
    z->setMaximum(400);
    z->setMinimum(-400);
    z->move(200, 220);
    z->setGeometry({200, 200, 20, 100});
    z->show();
    z_label.move(200, 200);

    edge = new QSlider(this);
    edge->setMaximum(10);
    edge->setMinimum(1);
    edge->move(200, 220);
    edge->setGeometry({300, 200, 20, 100});
    edge->show();
    edge_label.move(300, 200);

    QObject::connect(x, SIGNAL(valueChanged(int)),
                     this,   SLOT(_x(int)));
    QObject::connect(y, SIGNAL(valueChanged(int)),
                     this,   SLOT(_y(int)));
    QObject::connect(z, SIGNAL(valueChanged(int)),
                     this,   SLOT(_z(int)));
    QObject::connect(edge, SIGNAL(valueChanged(int)),
                     this,   SLOT(_EdgeChanged(int)));
}
