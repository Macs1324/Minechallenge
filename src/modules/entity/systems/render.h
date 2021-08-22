#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include <entity/ecs.h>

typedef struct
{
    unsigned int shaderProgram;
}RenderSystem;

RenderSystem newRenderSystem();
void renderSystemUpdate(RenderSystem* system, Ecs* ecs);

#endif