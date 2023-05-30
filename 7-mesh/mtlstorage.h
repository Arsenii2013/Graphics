#ifndef MTLSTORAGE_H
#define MTLSTORAGE_H

#include "mtlentry.h"

#include <fstream>

class MTLStorage
{
    MTLStorage(){
        add(MTLEntry());
    }

    std::map<std::string, MTLEntry> entrys;
public:
    MTLStorage(MTLStorage const&)               = delete;
    void operator=(MTLStorage const&)  = delete;

    static MTLStorage& getInstance()
    {
        static MTLStorage    instance; // Guaranteed to be destroyed.
        return instance;
    }

    void add(const MTLEntry& e){
        if(entrys.contains(e.name)){
            throw std::invalid_argument("MTL exists");
        }
        entrys.emplace(e.name, e);
    }

    void parse(const std::string& fname){
        std::ifstream is(fname);
        MTLEntry e;
        while(!is.eof()){
            is >> e;
            add(e);
        }
    }

    const MTLEntry& get(const std::string& name){
        if(!entrys.contains(name)){
            throw std::invalid_argument("MTL not found");
        }
        return entrys[name];
    }

    size_t size(){
        return entrys.size();
    }
};

#endif // MTLSTORAGE_H
