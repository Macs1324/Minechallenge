#ifndef ECS_C
#define ECS_C

#include "ecs.h"
#include <GLFW/glfw3.h>

Ecs ecsNew()
{
    Ecs r;
    r.nrEntities = 0;
    r.nrTransform = 0;
    r.nrMesh = 0;
    r.nrCamera = 0;
    
    return r;
}

Entity ecsAddEntity(Ecs* ecs)
{
    int index = -1;
    int generation = -1;
    for(int i = 0; i < ecs->nrEntities; i++)
    {
        if(!ecs->entityData[i].alive)
        {
            index = i;
            generation = ++ecs->entityData[i].generation;
            break;
        }
    }

    if(index == -1)
    {
        index = ecs->nrEntities++;
        generation = 0;
    }

    Entity r =  (Entity){index, generation};
    ecsAddComponent(ecs, r, ECS_TRANSFORM);
    ecs->entityData[index].alive = 1;

    return r;
}

EntityData* ecsGetEntity(Ecs* ecs, Entity entity)
{
    if(entity.index == -1)
    {
        printf("Entity handle is invalid, it's probably dead\n");
        return NULL;
    }
    if(entity.generation != ecs->entityData[entity.index].generation)
    {
        printf("Cannot get entity %d:   Generations do not match", entity.index);
        return NULL;
    }

    return &ecs->entityData[entity.index];
}
void ecsRemoveEntity(Ecs* ecs, Entity* entity)
{
    for(int i = ECS_COMPONENT_FIRST; i < ECS_NUMBER_COMPONENTS; i++)
    {
        //First we free all the components attached to the entity
        if(ecsGetEntity(ecs, *entity)->indices[i] != -1)
        {
            ecsRemoveComponent(ecs, *entity, i);
        }
    }

    //Making the data and the handle go ded
    ecsGetEntity(ecs, *entity)->alive = 0;
    entity->index = -1;
}

void ecsAddComponent(Ecs* ecs, Entity entity, ecsComponent component)
{
    //Some basic error handling to avoid "Use after free"
    if(entity.index == -1)
    {
        printf("Entity handle is invalid, it's probably dead\n");
        return;
    }
    if(entity.generation != ecs->entityData[entity.index].generation)
    {
        printf("Cannot add component %d:\n  Entity handle outdated, memory could have been reused\n", component);
        return;
    }
    int componentIndex;
    //A huge ass switch bc ya know, no templates
    switch(component)
    {
        case ECS_TRANSFORM:
            int index = -1;
            int generation = -1;
            //Scan for dead components
            for(int i = 0; i < ecs->nrTransform; i++)
            {
                if( !((Component*)(&ecs->transform[i]))->alive )
                {
                    generation = ++((Component*)(&ecs->transform[i]))->generation;
                    index = i;
                    break;
                }
            }
            //If not dead components were found (and therefore the index remained unchanged)
            if(index == -1)
            {
                //Add a new component
                index = ecs->nrTransform++;
                generation = 0;
            }
            componentIndex = index;

            //Just sum inialization
            ecs->transform[index] = cTransformNew();
            ecs->transform[index].data.parent = entity;
            ecs->transform[index].data.alive = 1;
            ecs->transform[index].data.generation = generation;
            break;
        
        case ECS_MESH:
            index = -1;
            generation = -1;
            //Scan for dead components
            for(int i = 0; i < ecs->nrMesh; i++)
            {
                if( !((Component*)(&ecs->mesh[i]))->alive )
                {
                    generation = ++((Component*)(&ecs->mesh[i]))->generation;
                    index = i;
                    break;
                }
            }
            //If not dead components were found (and therefore the index remained unchanged)
            if(index == -1)
            {
                //Add a new component
                index = ecs->nrMesh++;
                generation = 0;
            }
            componentIndex = index;

            //Just sum inialization
            ecs->mesh[index].data.parent = entity;
            ecs->mesh[index].data.alive = 1;
            ecs->mesh[index].data.generation = generation;
            break;

        case ECS_CAMERA:
            index = -1;
            generation = -1;
            //Scan for dead components
            for(int i = 0; i < ecs->nrCamera; i++)
            {
                if( !((Component*)(&ecs->camera[i]))->alive )
                {
                    generation = ++((Component*)(&ecs->camera[i]))->generation;
                    index = i;
                    break;
                }
            }
            //If not dead components were found (and therefore the index remained unchanged)
            if(index == -1)
            {
                //Add a new component
                index = ecs->nrCamera++;
                generation = 0;
            }
            componentIndex = index;


            //Just sum inialization
            ecs->camera[index] = cCameraNew();
            ecs->camera[index].data.parent = entity;
            ecs->camera[index].data.alive = 1;
            ecs->camera[index].data.generation = generation;
            if(ecs->nrCamera == 1)
            {
                ecs->data.mainCamera.index = index;
                ecs->data.mainCamera.generation = generation;
            }
            break;

        default:
            //Basically this should happen if I fuck up a component index
            //Or forget to add a branch to the switch
            printf("Cannot get component %d Component is invalid\n", component);
            break;
    }

    ecs->entityData[entity.index].indices[component] = componentIndex;
}
void* ecsGetComponent(Ecs* ecs, Entity entity, ecsComponent component)
{
    //Some basic error handling to avoid "Use after free"
    if(entity.index == -1)
    {
        printf("Entity handle is invalid, it's probably dead\n");
        return NULL;
    }
    if(entity.generation != ecs->entityData[entity.index].generation)
    {
        printf("Cannot get component %d:\n  Entity handle outdated, memory could have been reused\n", component);
        return NULL;
    }
    if(ecs->entityData[entity.index].indices[component] == -1)
    {
        printf("Cannot get component%d  Entity does not have such a component bound to it\n", component);
    }


    switch(component)
    {
        case ECS_TRANSFORM:
            //More component-specific error handling
            if(ecs->transform[ecs->entityData[entity.index].indices[component]].data.generation == -1)
            {
                printf("Cannot get component %d Component is dead", component);
                return NULL;
            }
            if(ecs->transform[ecs->entityData[entity.index].indices[component]].data.generation ==
                ecs->entityData[entity.index].generation)
            {
                return &ecs->transform[ecs->entityData[entity.index].indices[component]];
            }
            else
            {
                printf("Cannot get component %d Generations do not match", component);
                return NULL;
            }

        case ECS_MESH:
            //More component-specific error handling
            if(ecs->mesh[ecs->entityData[entity.index].indices[component]].data.generation == -1)
            {
                printf("Cannot get component %d Component is dead", component);
                return NULL;
            }
            if(ecs->mesh[ecs->entityData[entity.index].indices[component]].data.generation ==
                ecs->entityData[entity.index].generation)
            {
                return &ecs->mesh[ecs->entityData[entity.index].indices[component]];
            }
            else
            {
                printf("Cannot get component %d Generations do not match", component);
                return NULL;
            }

        case ECS_CAMERA:
            //More component-specific error handling
            if(ecs->camera[ecs->entityData[entity.index].indices[component]].data.generation == -1)
            {
                printf("Cannot get component %d Component is dead", component);
                return NULL;
            }
            if(ecs->camera[ecs->entityData[entity.index].indices[component]].data.generation ==
                ecs->entityData[entity.index].generation)
            {
                return &ecs->camera[ecs->entityData[entity.index].indices[component]];
            }
            else
            {
                printf("Cannot get component %d Generations do not match", component);
                return NULL;
            }

        default:
            printf("Cannot get component %d Component is invalid\n", component);
    }
}

void ecsRemoveComponent(Ecs* ecs, Entity entity, ecsComponent component)
{
    ((Component*)ecsGetComponent(ecs, entity, component))->alive = 0;
}

void ecsSetMainCameraEntity(Ecs* ecs, Entity cameraEntity)
{
    if(ecs->entityData[cameraEntity.index].indices[ECS_CAMERA] != -1)
    {
        ecs->data.mainCamera = cameraEntity;
    }
    else
    {
        printf("Cannot set an entity without a camera component as the main camera dumbass\n");
    }
}
Entity ecsGetMainCameraEntity(Ecs* ecs)
{
    return ecs->data.mainCamera;
}

void ecsFrameStart(Ecs* ecs)
{
    ecs->data.timeFrameStart = glfwGetTime();
}
void ecsFrameEnd(Ecs* ecs)
{
    ecs->data.timeDelta = glfwGetTime() - ecs->data.timeFrameStart;
    ecs->data.timeElapsed += ecs->data.timeDelta;
}

#endif