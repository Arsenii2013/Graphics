#include "strip.h"

void Strip::Construct(std::vector<GLfloat> pts, std::vector<GLfloat> cls, std::vector<GLfloat> nls){
    pointsCnt = pts.size();
    points = new GLfloat[pointsCnt];
    colors = new GLfloat[pointsCnt];
    normals = new GLfloat[pointsCnt];

    std::copy(pts.begin(), pts.end(), points);
    if(!cls.empty()){
        std::copy(cls.begin(), cls.end(), colors);
    }else{
        fillRandomColor();
    }
    if(!nls.empty()){
        std::copy(nls.begin(), nls.end(), normals);
    }else{
        calculateNormals();
    }
}

Strip::Strip(std::vector<GLfloat> pts, std::vector<GLfloat> cls, std::vector<GLfloat> nls){
    if((pts.size() != cls.size() && !cls.empty()) ||
       (pts.size() != nls.size() && !nls.empty())){
        throw std::invalid_argument("points and colors and normals vectors must be equal!");
    }
    Construct(pts, cls, nls);
}

Strip::Strip(std::vector<QVector4D> pts, std::vector<QVector4D> cls, std::vector<QVector4D> nls){
    if((pts.size() != cls.size() && !cls.empty()) ||
       (pts.size() != nls.size() && !nls.empty())){
        throw std::invalid_argument("points and colors and normals vectors must be equal!");
    }
    std::vector<GLfloat> ptsTo;
    std::vector<GLfloat> clsTo;
    std::vector<GLfloat> nlsTo;

    for(const auto& point : pts){
        ptsTo.emplace_back(point.x());
        ptsTo.emplace_back(point.y());
        ptsTo.emplace_back(point.z());
    }
    for(const auto& color : cls){
        clsTo.emplace_back(color.x());
        clsTo.emplace_back(color.y());
        clsTo.emplace_back(color.z());
    }
    for(const auto& normal : nls){
        nlsTo.emplace_back(normal.x());
        nlsTo.emplace_back(normal.y());
        nlsTo.emplace_back(normal.z());
    }
    Construct(ptsTo, clsTo, nlsTo);
}

Strip::~Strip(){
    //delete [] points;
    //delete [] colors;
}

void Strip::fillRandomColor(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0., 1.);
    for(int i = 0; i < pointsCnt; i++){
        colors[i] = dis(gen);
    }
}

void Strip::calculateNormals()
{
    throw std::invalid_argument("not implemented!");
}

void Strip::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    window->glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, points);
    window->glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, normals);

    window->glEnableVertexAttribArray(0);
    window->glEnableVertexAttribArray(1);

    window->glDrawArrays(GL_TRIANGLE_STRIP, 0, pointsCnt/3);

    window->glDisableVertexAttribArray(1);
    window->glDisableVertexAttribArray(0);
}
