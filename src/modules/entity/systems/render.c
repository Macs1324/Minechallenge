#ifndef SYSTEM_RENDER_C
#define SYSTEM_RENDER_C

#include <GL/glew.h>
#include "render.h"

RenderSystem newRenderSystem(unsigned int blockShaderProgram);
void renderSystemUpdate(RenderSystem* system, Ecs* ecs)
{
    for(int i = 0; i < ecs->nrEntity; i++)
    {
        cTransform* transform = &ecs->transform[ecs->entities[i].components[C_TRANSFORM]];

        if(ecs->entities[i].components[C_MESH] != -1)
        {
            cMesh* mesh = &ecs->mesh[ecs->entities[i].components[C_MESH]];
            glBindVertexArray(mesh->vertexArray);
            glUseProgram(system->shaderProgram);
            glDrawElements(GL_TRIANGLES, mesh->nrIndices, GL_UNSIGNED_INT, mesh->elementArray);
        }
    }
}

#endif