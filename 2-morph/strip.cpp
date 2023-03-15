#include "strip.h"

void Strip::Construct(std::vector<GLfloat> pts, std::vector<GLfloat> cls){
    pointsCnt = pts.size();
    points = new GLfloat[pointsCnt];
    colors = new GLfloat[pointsCnt];

    std::copy(pts.begin(), pts.end(), points);
    if(!cls.empty()){
        std::copy(cls.begin(), cls.end(), colors);
    }else{
        fillRandom();
    }
}

Strip::Strip(std::vector<GLfloat> pts, std::vector<GLfloat> cls){
    if(pts.size() != cls.size() && !cls.empty()){
        throw std::invalid_argument("points and colors vectors must be equal!");
    }
    Construct(pts, cls);
}

Strip::Strip(std::vector<QVector4D> pts, std::vector<QVector4D> cls){
    if(pts.size() != cls.size() && !cls.empty()){
        throw std::invalid_argument("points and colors vectors must be equal!");
    }
    std::vector<GLfloat> ptsTo;
    std::vector<GLfloat> clsTo;

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
    Construct(ptsTo, clsTo);
}

Strip::~Strip(){
    //delete [] points;
    //delete [] colors;
}

void Strip::fillRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0., 1.);
    for(int i = 0; i < pointsCnt; i++){
        colors[i] = dis(gen);
    }
}

void Strip::draw(GLuint m_posAttr, GLuint m_colAttr, QOpenGLFunctions *window){
    window->glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, points);
    window->glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    window->glEnableVertexAttribArray(0);
    window->glEnableVertexAttribArray(1);

    window->glDrawArrays(GL_TRIANGLE_STRIP, 0, pointsCnt/3);

    window->glDisableVertexAttribArray(1);
    window->glDisableVertexAttribArray(0);
}
