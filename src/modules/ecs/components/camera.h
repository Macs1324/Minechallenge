#ifndef C_CAMERA_H
#define C_CAMERA_H

#include <cglm/cglm.h>
#include "componentInterface.h"

typedef struct
{
    Component data;
    float fov;
    float clipNear;
    float clipFar;
}cCamera;

cCamera cCameraNew();

#endif