#include "cube.h"

#include <random>
#include <algorithm>

namespace{
bool operator==(std::pair<GraphicObj::Type, int> rhs, std::pair<GraphicObj::Type, int> lhs){
    return rhs.first == lhs.first && rhs.second == lhs.second;
}
class Cache
{
    Cache() {}
    ~Cache() {}

    std::map<std::pair<GraphicObj::Type, int>, std::shared_ptr<std::vector<CubeSide>>> cc;
public:
    static Cache & getInstance(){
        static Cache s;
        return s;
    }

    Cache(const Cache &) = delete;
    Cache & operator = (const Cache &) = delete;

    std::shared_ptr<std::vector<CubeSide>> get(int pointsPerSide, GraphicObj::Type type){
        auto key = std::make_pair(type, pointsPerSide);
        if(!cc.contains(key)){
            cc.insert({key, std::make_shared<std::vector<CubeSide>>()});
            std::string ttype;
            if(type == GraphicObj::Type::CUBE){
                ttype = "cube";
            }else if(type == GraphicObj::Type::BALL){
                ttype = "ball";
            }

            QMatrix4x4 noRotate;
            cc[key]->emplace_back(pointsPerSide, noRotate, ttype);
            QMatrix4x4 rotate90aboutY;
            rotate90aboutY.rotate(90.f, 0, 1, 0);
            cc[key]->emplace_back(pointsPerSide, rotate90aboutY, ttype);
            QMatrix4x4 rotate180aboutY;
            rotate180aboutY.rotate(180.f, 0, 1, 0);
            cc[key]->emplace_back(pointsPerSide, rotate180aboutY, ttype);
            QMatrix4x4 rotate270aboutY;
            rotate270aboutY.rotate(270.f, 0, 1, 0);
            cc[key]->emplace_back(pointsPerSide, rotate270aboutY, ttype);
            QMatrix4x4 rotate90aboutX;
            rotate90aboutX.rotate(90.f, 1, 0, 0);
            cc[key]->emplace_back(pointsPerSide, rotate90aboutX, ttype);
            QMatrix4x4 rotate270aboutX;
            rotate270aboutX.rotate(270.f, 1, 0, 0);
            cc[key]->emplace_back(pointsPerSide, rotate270aboutX, ttype);
        }
        return cc[key];
    }
};
}

GraphicObj::GraphicObj(QVector3D center, GLfloat side, int pointsPerSide, Type type) {
    if(pointsPerSide < 2){
        //throw std::invalid_argument("i cant gen side withs less then 2 points");
    }

    sides = Cache::getInstance().get(pointsPerSide, type);

    selfScale(QVector3D{side/2, side/2, side/2});
    selfTranslate(center);
}

void GraphicObj::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    for(auto& side : *sides){
        side.draw(m_posAttr, m_colAttr, window);
    }
}
/*
void ColorPosCube::setColor(Side side, GLfloat r, GLfloat g, GLfloat b){
    if(primitive == GL_TRIANGLES){
        int start_pos;
        switch (side){
        case Side::FRONT:
            start_pos = 0;
            break;
        case Side::BACK:
            start_pos = 3 * pointsCnt / 6 * 3;
            break;
        case Side::RIGHT:
            start_pos = pointsCnt / 6 * 3;
            break;
        case Side::LEFT:
            start_pos = 2 * pointsCnt / 6 * 3;
            break;
        case Side::UP:
            start_pos = 4 * pointsCnt / 6 * 3;
            break;
        case Side::DOWN:
            start_pos = 5 * pointsCnt / 6 * 3;
            break;
        }
        for(int i = 0; i < pointsCnt / 6 ; i++){
            colors[i*3 + start_pos] = r;  colors[i*3 + 1 + start_pos] = g;  colors[i*3 + 2 + start_pos] = b;
        }
    }else if(primitive == GL_TRIANGLE_STRIP){
        throw std::invalid_argument("unsupported primitive");
    }
}

void ColorPosCube::setColor(Side side, QColor color){
    setColor(side, color.red(), color.green(), color.blue());
}

void ColorPosCube::setColor(Side side, QColor up_left, QColor up_right, QColor down_left, QColor down_right){
    throw std::invalid_argument("unsupported func!");
}

void ColorPosCube::setColor(GLfloat r, GLfloat g, GLfloat b){
    setColor(ColorPosCube::Side::FRONT, r, g, b);
    setColor(ColorPosCube::Side::BACK, r, g, b);
    setColor(ColorPosCube::Side::RIGHT, r, g, b);
    setColor(ColorPosCube::Side::LEFT, r, g, b);
    setColor(ColorPosCube::Side::DOWN, r, g, b);
    setColor(ColorPosCube::Side::UP, r, g, b);
}

int ColorPosCube::getPointsCnt(){
    return pointsCnt;
}
*/
