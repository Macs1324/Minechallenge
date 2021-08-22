#ifndef ENTITY_H
#define ENTITY_H

enum Components
{
    C_TRANSFORM,
    C_MESH
};

#define NrCOMPONENTS 2

typedef struct
{
    unsigned int generation;
    unsigned int components[NrCOMPONENTS];
}Entity;

typedef struct EntityHandle
{
    unsigned int index;
    unsigned int generation;
}EntityHandle;
#endif