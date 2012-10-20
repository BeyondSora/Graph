#ifndef RESOURCE_H
#define RESOURCE_H

// Dependencies
#include <cstdint>
#include <map>
#include <utility>
#include "ModelTypes.h"

class Storage {
public:
    typedef uint32_t RefCount;
    typedef std::pair<Edge*,   RefCount> EdgePair;
    typedef std::pair<Vertex*, RefCount> VertexPair;

    static Storage& Instance() { return instance_; }

    Edge*   getEdge   (const Identity id);    // may throw
    Vertex* getVertex (const Identity id);    // may throw

    void reg   (Edge   *e);   // may throw
    void reg   (Vertex *v);   // may throw
    void ref   (const Edge   *e);
    void ref   (const Vertex *v);
    void unref (const Edge   *e);
    void unref (const Vertex *v);
private:
    static Storage instance_;
    std::map<Identity, EdgePair>   eRef_;
    std::map<Identity, VertexPair> vRef_;

    void unreg   (const Edge   *e);
    void unreg   (const Vertex *v);
};

#define Stack Storage::Instance()

#endif//RESOURCE_H
