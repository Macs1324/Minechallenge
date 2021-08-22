#ifndef COMPONENT_MESH_H
#define COMPONENT_MESH_H

#include <cglm/cglm.h>

typedef struct
{
    vec3 pos;
    vec2 uv;
}MeshVertex;

typedef struct
{
    unsigned int vertexBuffer;
    unsigned int vertexArray;
    unsigned int* elementArray;
    unsigned int nrIndices;
}cMesh;

cMesh newMesh();

#endif