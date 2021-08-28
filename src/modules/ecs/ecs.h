#ifndef ECS_H
#define ECS_H

#include <util/util.h>
#include "components/components.h"
#include <shader/shader.h>

#define MAX_ENTITIES 5000

typedef enum 
{
    ECS_COMPONENT_FIRST,
    ECS_TRANSFORM,
    ECS_MESH,
    ECS_CAMERA,
    ECS_NUMBER_COMPONENTS,
}ecsComponent;

typedef GenerationalIndex Entity;

typedef struct
{
    GenerationalIndex parent;
    int generation;
    int alive;
    int indices[ECS_NUMBER_COMPONENTS]; //If index is -1 then entity doesn't have that component on it
}EntityData;

typedef struct
{
    double timeFrameStart;
    double timeElapsed;
    double timeDelta;
    float screenWidth;
    float screenHeight;
    Shader meshShaderProgram;
    GenerationalIndex mainCamera;
}EcsData;

typedef struct
{
    EcsData data;
    EntityData entityData[MAX_ENTITIES];
    unsigned int nrEntities;

    cTransform transform[MAX_ENTITIES];
    unsigned int nrTransform;

    cMesh mesh[MAX_ENTITIES];
    unsigned int nrMesh;

    cCamera camera[MAX_ENTITIES];
    unsigned int nrCamera;
}Ecs;

Ecs ecsNew();

Entity ecsAddEntity(Ecs* ecs);
EntityData* ecsGetEntity(Ecs* ecs, Entity entity);
void ecsRemoveEntity(Ecs* ecs, Entity* entity);

void ecsAddComponent(Ecs* ecs, Entity entity, ecsComponent component);
void* ecsGetComponent(Ecs* ecs, Entity entity, ecsComponent component);
//Usage:
//cTransform transform= ecsGetComponent(&world, entityIndex, ECS_TRANSFORM);
void ecsRemoveComponent(Ecs* ecs, Entity entity, ecsComponent component);
void ecsSetMainCameraEntity(Ecs* ecs, Entity cameraEntity);
Entity ecsGetMainCameraEntity(Ecs* ecs);
void ecsFrameStart(Ecs* ecs);
void ecsFrameEnd(Ecs* ecs);

#endif