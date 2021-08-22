#ifndef ECS_H
#define ECS_H

#include <entity/entity.h>
#include "components/transform.h"
#include "components/mesh.h"

#define MAX_ENTITIES 5000

typedef struct
{
    Entity entities[MAX_ENTITIES];
    unsigned int nrEntity;


    cTransform transform[MAX_ENTITIES];
    unsigned int nrTransform;

    cMesh mesh[MAX_ENTITIES];
    unsigned int nrMesh;
}Ecs;

Entity entityNew();
Ecs ecsNew();
EntityHandle ecsAddEntity(Ecs* ecs);
Entity* ecsGetEntity(Ecs* ecs, EntityHandle handle);
void ecsRemoveEntity(Ecs* ecs, EntityHandle handle);

#endif