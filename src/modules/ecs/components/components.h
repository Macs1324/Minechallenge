#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "transform.h"
#include "mesh.h"
#include "camera.h"

cTransform cTransformNew();
cCamera cCameraNew();
void cMeshLoadVertices(cMesh* r, float vertices[], int nrVertices, unsigned int indices[], int nrIndices);
void cMeshLoadTexture(cMesh* r, const char* filename);


#endif