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
    unsigned int texture
}cMesh;

cMesh meshNew();

#endif