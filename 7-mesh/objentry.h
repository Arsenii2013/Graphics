#ifndef OBJENTRY_H
#define OBJENTRY_H

#include <QVector3D>
#include <QtGui/QOpenGLFunctions>
#include <iostream>
#include <string>

#include "mtlentry.h"
#include "shaderwrapper.h"

class OBJEntry
{
public:
    enum class Type{
        TRI,
        QUAD,
    };
private:
    std::string name;
    GLfloat *pos;
    GLfloat *nor;
    GLfloat *tex;
    int pointsCnt;
    const MTLEntry& mtl;
    OBJEntry::Type type;
    void Construct(std::vector<GLfloat> pts, std::vector<GLfloat> nls, std::vector<GLfloat> txs){
        pointsCnt = pts.size();
        pos = new GLfloat[pointsCnt];
        nor = new GLfloat[pointsCnt];
        tex = new GLfloat[pointsCnt];

        std::copy(pts.begin(), pts.end(), pos);

        if(!nls.empty()){
            std::copy(nls.begin(), nls.end(), nor);
        }
        if(!txs.empty()){
            std::copy(txs.begin(), txs.end(), tex);
        }
    }

public:
    OBJEntry(): mtl(MTLEntry()){}

    OBJEntry(OBJEntry::Type t, std::string name, const MTLEntry& mtl, std::vector<GLfloat> pts, std::vector<GLfloat> nls, std::vector<GLfloat> txs)
        : name(name), mtl(mtl), type(t){
        if((pts.size() != nls.size() && !nls.empty())){
            throw std::invalid_argument("points and colors and normals vectors must be equal!");
        }
        Construct(pts, nls, txs);
    }

    OBJEntry(OBJEntry::Type t, std::string name, const MTLEntry& mtl, std::vector<QVector3D> pts, std::vector<QVector3D> nls, std::vector<QVector2D> txs)
        : name(name), mtl(mtl), type(t){
        if((pts.size() != nls.size() && !nls.empty())){
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
        for(const auto& color : nls){
            clsTo.emplace_back(color.x());
            clsTo.emplace_back(color.y());
            clsTo.emplace_back(color.z());
        }
        for(const auto& normal : txs){
            nlsTo.emplace_back(normal.x());
            nlsTo.emplace_back(normal.y());
        }
        Construct(ptsTo, clsTo, nlsTo);
    }

    void draw(GLuint m_pos, GLuint m_nor, GLuint m_tex, QOpenGLFunctions *window) const{
        window->glVertexAttribPointer(m_pos, 3, GL_FLOAT, GL_FALSE, 0, pos);
        if(m_nor != GLuint(-1))
            window->glVertexAttribPointer(m_nor, 3, GL_FLOAT, GL_FALSE, 0, nor);
        if(m_tex != GLuint(-1))
            window->glVertexAttribPointer(m_tex, 3, GL_FLOAT, GL_FALSE, 0, tex);

        window->glEnableVertexAttribArray(0);
        if(m_nor != GLuint(-1))
            window->glEnableVertexAttribArray(1);
        if(m_tex != GLuint(-1))
            window->glEnableVertexAttribArray(2);

        if(type == OBJEntry::Type::TRI)
            window->glDrawArrays(GL_TRIANGLES, 0, pointsCnt/3);
        if(type == OBJEntry::Type::QUAD)
            window->glDrawArrays(GL_QUADS, 0, pointsCnt/4);

        if(m_tex != GLuint(-1))
            window->glDisableVertexAttribArray(2);
        if(m_nor != GLuint(-1))
            window->glDisableVertexAttribArray(1);
        window->glDisableVertexAttribArray(0);

    }

    void setMTL(ShaderWrapper& shader){
        //TODO set all parameters within correspond names
    }

    const std::string& getName() const{
        return name;
    }
};

#endif // OBJENTRY_H
