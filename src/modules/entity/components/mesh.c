#ifndef COMPONENT_MESH_C
#define COMPONENT_MESH_C

#include <GL/glew.h>
#include "mesh.h"

cMesh meshNew(MeshVertex* vertices, unsigned int nVertices, unsigned int texture)
{
    cMesh r;
    glGenBuffers(1, &r.vertexBuffer);
    glGenVertexArrays(1, &r.vertexArray);
    glBindVertexArray(r.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, r.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(MeshVertex), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return r;
}

#endif