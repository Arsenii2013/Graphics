#include "settings.h"
#include <chrono>

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
    shader->setCurrentIndex(2);
    shader->move(100, 100);
    //shader->show();

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
    x->setGeometry({0, 200, 20, 100});
    x->show();
    x_label.move(0, 200);

    y = new QSlider(this);
    y->setMaximum(400);
    y->setMinimum(-400);
    y->setGeometry({100, 200, 20, 100});
    y->show();
    y_label.move(100, 200);

    z = new QSlider(this);
    z->setMaximum(400);
    z->setMinimum(-400);
    z->setGeometry({200, 200, 20, 100});
    z->show();
    z_label.move(200, 200);

    edge = new QSlider(this);
    edge->setMaximum(10);
    edge->setMinimum(1);
    edge->setGeometry({300, 200, 20, 100});
    edge->show();
    edge_label.move(300, 200);

    cubes = new QSlider(this);
    cubes->setMaximum(100);
    cubes->setMinimum(1);
    cubes->setGeometry({400, 200, 20, 100});
    cubes->show();
    cubes_label.move(400, 200);

    lights_cnt = new QSlider(this);
    lights_cnt->setMaximum(100);
    lights_cnt->setMinimum(0);
    lights_cnt->setGeometry({0, 300, 20, 100});
    lights_cnt->show();
    lights_cnt_label.move(0, 300);

    QObject::connect(x, SIGNAL(valueChanged(int)),
                     this,   SLOT(_x(int)));
    QObject::connect(y, SIGNAL(valueChanged(int)),
                     this,   SLOT(_y(int)));
    QObject::connect(z, SIGNAL(valueChanged(int)),
                     this,   SLOT(_z(int)));
    QObject::connect(edge, SIGNAL(valueChanged(int)),
                     this,   SLOT(_EdgeChanged(int)));
    QObject::connect(cubes, SIGNAL(valueChanged(int)),
                     this,   SLOT(_CubesChanged(int)));
    QObject::connect(lights_cnt, SIGNAL(valueChanged(int)),
                     this,   SLOT(_LightsCntChanged(int)));


    FPS.setGeometry({500, 200, 150, 100});
}

void Settings::frame(){
    auto now = std::chrono::steady_clock::now();
    static auto prev = now;

    double elapsed = std::chrono::duration<double>(now - prev).count();

    sec_per_frame.push_back(elapsed);
    static int average = 0;
    if(std::accumulate(sec_per_frame.begin(), sec_per_frame.end(), 0.d) > 1.d){
        average = sec_per_frame.size();
        sec_per_frame.clear();
    }
    FPS.setText(QString::fromStdString(std::string("frame: " + std::to_string(1.f/elapsed) + "\naverage: " + std::to_string(average))));
    prev = now;
}
