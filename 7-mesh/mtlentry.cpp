#include "mtlentry.h"


std::istream &operator>>(std::istream &is, QVector3D &v)
{
    float x, y, z;
    is>>x>>y>>z;
    v.setX(x);
    v.setY(y);
    v.setZ(z);
    return is;
}

std::istream &operator>>(std::istream &is, MTLEntry &e)
{
    std::string opt;
    bool mtl_gated = false;
    while(!is.eof()){
        is>>opt;
        if(opt == "#" || opt == "map_Kd" || opt == "s"){
            std::string useless{};
            std::getline(is, useless);
        }
        if(opt == "newmtl"){
            if(mtl_gated){
                for(int i = 0; i < 6; i++)
                    is.unget();
                return is;
            }
            mtl_gated = true;
            is >> e.name;
        }

        if(opt == "Ka"){
            is >> e.Ka;
        }
        if(opt == "Kd"){
            is >> e.Kd;
        }
        if(opt == "Ks"){
            is >> e.Ks;
        }
        if(opt == "Ns"){
            float tmp;
            is>>tmp;
            e.Ns = tmp;
        }
        if(opt == "d"){
            float tmp;
            is>>tmp;
            e.d = tmp;
        }
    }
    return is;
}
