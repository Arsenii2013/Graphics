#include "side.h"

#include <iostream>

constexpr int CubeSide::getStripSize(int pointsPerSide){
    return pointsPerSide*2;
}

namespace{
QVector4D cube_cord(QVector4D pos){
    return pos;
}

QVector4D cube_norm(QVector4D pos){
    return {0, 0, -1, 1};
}

QVector4D ball_cord(QVector4D pos){
    QVector3D pos3{pos};
    return {pos3.normalized(), 1};
}

QVector4D ball_norm(QVector4D pos){
    QVector3D pos3{pos};
    return {pos3.normalized(), 1};
}

std::map<CubeSide::Type, std::function<QVector4D (QVector4D)>> cord_gens{
    {CubeSide::Type::CUBE, cube_cord},
    {CubeSide::Type::BALL, ball_cord}
};
std::map<CubeSide::Type, std::function<QVector4D (QVector4D)>> norm_gens{
  {CubeSide::Type::CUBE, cube_norm},
  {CubeSide::Type::BALL, ball_norm}
};

# define PI           3.14159265358979323846  /* pi */
}


void CubeSide::genCube(int pointsPerSide, QMatrix4x4 transform){
    GLfloat x = -0.5f;
    GLfloat y = -0.5f;
    GLfloat z = -0.5f;
    GLfloat dx = 1.f / pointsPerSide;
    GLfloat dy = 1.f / pointsPerSide;

    for(int i = 0; i < pointsPerSide; i++){
        std::vector<QVector4D> res;
        std::vector<QVector4D> normals;
        std::vector<QVector4D> colors;
        for(int j = 0; j <= pointsPerSide; j++){
            QVector4D first{x + i*dx, y+j*dy, -0.5, 1.};
            QVector4D second{x + (i + 1)*dx, y+j*dy, -0.5, 1.};
            res.emplace_back(transform * cord_gens[CubeSide::Type::CUBE](first));
            res.emplace_back(transform * cord_gens[CubeSide::Type::CUBE](second));
            normals.emplace_back(transform.inverted().transposed() * norm_gens[CubeSide::Type::CUBE](first));
            normals.emplace_back(transform.inverted().transposed() * norm_gens[CubeSide::Type::CUBE](second));
            colors.emplace_back(1, 1, 1, 1);
            colors.emplace_back(1, 1, 1, 1);
        }
        strips.emplace_back(res, colors, normals);
    }
}

void CubeSide::genBall(int pointsPerSide, QMatrix4x4 transform){
    GLfloat phi = 0.f;
    GLfloat theta = 0.f;

    GLfloat dphi = 2.f * PI / (pointsPerSide * 4); //0 - 2pi
    GLfloat dtheta = PI / (pointsPerSide * 4); //0 - pi

    for(int i = 0; i < pointsPerSide * 4; i++){
        std::vector<QVector4D> res;
        std::vector<QVector4D> normals;
        std::vector<QVector4D> colors;
        for(int j = 0; j <= pointsPerSide * 4; j++){
            QVector4D first{std::sin(theta + dtheta * i) * std::cos(phi + dphi * j), std::cos(theta + dtheta * i), std::sin(theta + dtheta * i) * std::sin(phi + dphi * j), 1.};
            QVector4D second{std::sin(theta + dtheta * (i + 1)) * std::cos(phi + dphi * j), std::cos(theta + dtheta * (i + 1)), std::sin(theta + dtheta * (i + 1)) * std::sin(phi + dphi * j), 1.};
            res.emplace_back(transform * cord_gens[CubeSide::Type::BALL](first));
            res.emplace_back(transform * cord_gens[CubeSide::Type::BALL](second));
            normals.emplace_back(transform.inverted().transposed() * norm_gens[CubeSide::Type::BALL](first));
            normals.emplace_back(transform.inverted().transposed() * norm_gens[CubeSide::Type::BALL](second));
            colors.emplace_back(1, 1, 1, 1);
            colors.emplace_back(1, 1, 1, 1);
        }
        strips.emplace_back(res, colors, normals);
    }
}

CubeSide::CubeSide(int pointsPerSide, QMatrix4x4 transform, CubeSide::Type type){
    if(type == CubeSide::Type::CUBE){
        genCube(pointsPerSide, transform);
    }

    if(type == CubeSide::Type::BALL){
        genBall(pointsPerSide, transform);
    }
}

void CubeSide::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    for(auto& strip : strips){
        strip.draw(m_posAttr, m_colAttr, window);
    }
}
