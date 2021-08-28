#ifndef C_TRANSFORM_H
#define C_TRANSFORM_H

#include <cglm/cglm.h>
#include <util/util.h>
#include "componentInterface.h"

typedef struct
{
    Component data;
    vec3 position;
    vec3 rotation;
    vec3 scale;
}cTransform;

#endif