#include "side.h"


constexpr int CubeSide::getStripSize(int pointsPerSide){
    return pointsPerSide*2;
}

CubeSide::CubeSide(int pointsPerSide, QMatrix4x4 transform, std::function<GLfloat (GLfloat, GLfloat)>   z_gen,
                                                  std::function<QVector4D (GLfloat, GLfloat)> normal_gen,
                                                  std::function<QVector4D (GLfloat, GLfloat)> color_gen){
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
            res.emplace_back(transform * QVector4D(x + i*dx, y+j*dy, z_gen(x + i*dx, y+j*dy), 1));
            res.emplace_back(transform * QVector4D(x + (i + 1)*dx, y+j*dy, z_gen(x + (i + 1)*dx, y+j*dy), 1));
            normals.emplace_back((transform.inverted().transposed() * normal_gen(x + i*dx, y+j*dy)).normalized());
            normals.emplace_back((transform.inverted().transposed() * normal_gen(x + (i + 1)*dx, y+j*dy)).normalized());
            colors.emplace_back(color_gen(x + i*dx, y+j*dy));
            colors.emplace_back(color_gen(x + (i + 1)*dx, y+j*dy));
        }
        strips.emplace_back(res, colors, normals);
    }
}

namespace {
GLfloat cubeZ(GLfloat x, GLfloat y){
    return -0.5f;
}

QVector4D cubeNormal(GLfloat x, GLfloat y){
    return -QVector4D(0., 0., 1., 1.);
}

GLfloat ballZ(GLfloat x, GLfloat y){
    return -std::sqrt(0.25f - x*x - y*y);
}

QVector4D ballNormal(GLfloat x, GLfloat y){
    return QVector4D(x, y, ballZ(x, y), 1.);
}

QVector4D whiteColor(GLfloat x, GLfloat y){
    return QVector4D(1., 1., 1., 1.);
}
std::map<std::string, std::function<GLfloat (GLfloat, GLfloat)>> z_gens = {{"cube", cubeZ},
                                                                           {"ball", ballZ}};

std::map<std::string, std::function<QVector4D (GLfloat, GLfloat)>> normal_gens = {{"cube", cubeNormal},
                                                                                  {"ball", ballNormal}};

std::map<std::string, std::function<QVector4D (GLfloat, GLfloat)>> color_gens = {{"cube", whiteColor},
                                                                                 {"ball", whiteColor}};
}

CubeSide::CubeSide(int pointsPerSide, QMatrix4x4 transform, std::string type): CubeSide(pointsPerSide, transform, z_gens[type], normal_gens[type], color_gens[type]){
}

void CubeSide::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    for(auto& strip : strips){
        strip.draw(m_posAttr, m_colAttr, window);
    }
}
