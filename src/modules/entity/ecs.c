#ifndef ECS_C
#define ECS_C

#include "ecs.h"

Entity entityNew()
{
    Entity r;
    r.generation = 0;
    for(int i = 0; i < NrCOMPONENTS; i++)
    {
        r.components[i] = -1;
    }

    return r;
}

Ecs ecsNew()
{
    Ecs r;
    r.nrEntity = 0;
    r.nrMesh = 0;
    r.nrTransform = 0;
}

EntityHandle ecsAddEntity(Ecs* ecs)
{
    ecs->entities[ecs->nrEntity] = entityNew();
    EntityHandle r = {ecs->nrEntity, 0};
    ecs->nrEntity += 1;
    return r;
}
Entity* ecsGetEntity(Ecs* ecs, EntityHandle handle)
{
    if(handle.generation == ecs->entities[handle.index].generation)
    {
        return &(ecs->entities[handle.index]);
    }
    else
    {
        return NULL;
    }
}
void ecsRemoveEntity(Ecs* ecs, EntityHandle handle)
{
    // (Entity*)(&ecs->entities[handle.index]) = NULL;
}

#endif