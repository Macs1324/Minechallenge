#ifndef COMPONENTS_C
#define COMPONENTS_C

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "components.h"

cTransform cTransformNew()
{
    cTransform r;
    glm_vec3_zero(r.position);
    glm_vec3_zero(r.rotation);
    glm_vec3_one(r.scale);

    return r;
}

cCamera cCameraNew()
{
    cCamera r;
    r.fov = 3.14 / 3.0;
    r.clipNear = 0.01;
    r.clipFar = 1024.0;

    return r;
}

void cMeshLoadVertices(cMesh* r, float vertices[], int nrVertices, unsigned int indices[], int nrIndices)
{
    glGenBuffers(1, &r->vertexBuffer);
    glGenBuffers(1, &r->elementArray);
    glGenVertexArrays(1, &r->vertexArray);


    glBindVertexArray(r->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, r->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nrVertices * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->elementArray);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
    r->nrIndices = nrIndices;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

//FUCKING DELETE THIS ASAP, THIS IS FOR DEBUGGING FOR CHRIST'S SAKE
void cMeshDraw(cMesh* mesh, unsigned int shaderProgram)
{
    glBindVertexArray(mesh->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementArray);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->texture);

    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, mesh->nrIndices, GL_UNSIGNED_INT, 0);
}

void cMeshLoadTexture(cMesh* r, const char* filename)
{
    stbi_set_flip_vertically_on_load(1);
    glGenTextures(1, &r->texture);
    glBindTexture(GL_TEXTURE_2D, r->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int w, h, c;
    unsigned char* textureData = stbi_load(filename, &w, &h, &c, 0);
    

    if(textureData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture!\n");
    }

    // stbi_image_free(textureData);
}
#endif