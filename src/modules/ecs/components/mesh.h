#ifndef C_MESH_H
#define C_MESH_H

#include "componentInterface.h"
#include <cglm/cglm.h>

typedef struct
{
    Component data;
    unsigned int vertexBuffer;
    unsigned int vertexArray;
    unsigned int elementArray;
    unsigned int nrIndices;
    unsigned int texture;
}cMesh;

void cMeshLoadVertices(cMesh* r, float vertices[], int nrVertices, unsigned int indices[], int nrIndices);
void cMeshLoadTexture(cMesh* r, const char* filename);

//FOR DEBUG! REMOVE THIS ASAP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void cMeshDraw(cMesh* mesh, unsigned int shaderProgram);

#endif