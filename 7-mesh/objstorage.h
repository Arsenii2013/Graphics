#ifndef OBJSTORAGE_H
#define OBJSTORAGE_H

#include "objentry.h"
#include "mtlstorage.h"

#include <iostream>

namespace{
class OBJParser{

public:
    static OBJEntry parse(std::istream& is){
        std::string name;
        std::string mtl_name;
        std::vector<QVector3D> vert;
        std::vector<QVector3D> norm;
        std::vector<QVector2D> text;
        std::string opt;

        std::vector<GLfloat> pos;
        std::vector<GLfloat> nor;
        std::vector<GLfloat> tex;
        bool go_gated = false;
        bool is_tri = false;
        bool is_quad = false;
        while(is){
            is>>opt;
            //std::cout << is.gcount() << std::endl;
            if(opt == "#"){
                std::string useless{};
                std::getline(is, useless);
            }
            if(opt == "g" || opt == "o"){
                if(go_gated){
                    if(is_tri && !is_quad)
                        return {OBJEntry::Type::TRI, name, MTLStorage::getInstance().get(mtl_name), pos, nor, tex};
                    if(!is_tri && is_quad)
                        return {OBJEntry::Type::QUAD, name, MTLStorage::getInstance().get(mtl_name), pos, nor, tex};
                    return {};
                }
                go_gated = true;
                is >> name;
            }
            if(opt == "v"){
                QVector3D v;
                is >> v;
                vert.push_back(v);
            }
            if(opt == "vn"){
                QVector3D vn;
                is >> vn;
                norm.push_back(vn);
            }
            if(opt == "vt"){
                GLfloat vtx, vty;
                is >> vtx >> vty;
                text.emplace_back(vtx, vty);
            }
            if(opt == "mtllib"){
                std::string fname;
                //is>>fname;
                //MTLStorage::getInstance().parse(fname);
            }
            if(opt == "usemtl"){
                //is>>mtl_name;
            }
            if(opt == "f"){
                std::string tri;
                int cnt = 0;
                while(!is.eof() && is>>tri && tri != "f"){
                    int vi, vni, vti;
                    if(sscanf(tri.c_str(), "%i/%i/%i", &vi, &vni, &vti) == 3){
                        pos.push_back(vert[vi-1].x());
                        pos.push_back(vert[vi-1].y());
                        pos.push_back(vert[vi-1].z());
                        nor.push_back(norm[vni-1].x());
                        nor.push_back(norm[vni-1].y());
                        nor.push_back(norm[vni-1].z());
                        tex.push_back(text[vti-1].x());
                        tex.push_back(text[vti-1].y());
                    }

                    if(sscanf(tri.c_str(), "%i//%i", &vi, &vni) == 2){
                        pos.push_back(vert[vi-1].x());
                        pos.push_back(vert[vi-1].y());
                        pos.push_back(vert[vi-1].z());
                        nor.push_back(norm[vni-1].x());
                        nor.push_back(norm[vni-1].y());
                        nor.push_back(norm[vni-1].z());
                    }
                    cnt++;
                }
                if((cnt == 3) && !is.eof()){
                    is_tri = true;
                }
                if((cnt == 2) && is.eof()){
                    is_tri = true;
                }
                if((cnt == 3) && is.eof()){
                    is_quad = true;
                }
                if(cnt == 4){
                    is_quad = true;
                }
                is.unget();
            }
        }
        if(is_tri)
            return {OBJEntry::Type::TRI, name, MTLStorage::getInstance().get(mtl_name), pos, nor, tex};
        if(is_quad)
            return {OBJEntry::Type::QUAD, name, MTLStorage::getInstance().get(mtl_name), pos, nor, tex};
        return {};
    }
};
}
class OBJStorage
{
    OBJStorage() = default;

    std::map<std::string, OBJEntry> entrys;
public:
    OBJStorage(OBJStorage const&)               = delete;
    void operator=(OBJStorage const&)  = delete;

    static OBJStorage& getInstance()
    {
        static OBJStorage    instance; // Guaranteed to be destroyed.
        return instance;
    }

    void add(const OBJEntry& e){
        if(entrys.contains(e.getName())){
            throw std::invalid_argument("OBJ exists");
        }
        entrys.emplace(e.getName(), e);
    }

    void parse(const std::string& fname){
        std::ifstream is(fname);
        while(is){
            add(OBJParser::parse(is));
        }
    }

    const OBJEntry& get(const std::string& name){
        if(!entrys.contains(name)){
            throw std::invalid_argument("OBJ not found");
        }
        return entrys.at(name);
    }

    size_t size(){
        return entrys.size();
    }
};
#endif // OBJSTORAGE_H
