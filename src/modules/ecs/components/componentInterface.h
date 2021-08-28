#ifndef COMPONENT_INTERFACE_H
#define COMPONENT_INTERFACE_H

#include <util/util.h>

typedef struct
{
    int generation;
    int alive;
    GenerationalIndex parent;
}Component;

#endif