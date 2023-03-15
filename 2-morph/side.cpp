#include "side.h"


constexpr int CubeSide::getStripSize(int pointsPerSide){
    return pointsPerSide*2;
}

std::vector<Strip> CubeSide::genTriangleStrip(int pointsPerSide, QMatrix4x4 transform){
    std::vector<Strip> stripp;
    pointsPerSide -= 1;
    GLfloat x = -0.5f;
    GLfloat y = -0.5f;
    GLfloat z = -0.5f;
    GLfloat dx = 1.f / pointsPerSide;
    GLfloat dy = 1.f / pointsPerSide;

    for(int i = 0; i < pointsPerSide; i++){
        std::vector<QVector4D> res;
        for(int j = 0; j <= pointsPerSide; j++){
            res.emplace_back(transform * QVector4D(x + i*dx, y+j*dy, z, 1));
            res.emplace_back(transform * QVector4D(x + (i + 1)*dx, y+j*dy, z, 1));
        }
        stripp.emplace_back(res);
    }
    return stripp;
}

CubeSide::CubeSide(int pointsPerSide, QMatrix4x4 transform){
    strips = genTriangleStrip(pointsPerSide, transform);
}

void CubeSide::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    for(auto& strip : strips){
        strip.draw(m_posAttr, m_colAttr, window);
    }
}
