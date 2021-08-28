#ifndef ECS_SYSTEMS_H
#define ECS_SYSTEMS_H

#include <ecs/ecs.h>
#include <GLFW/glfw3.h>

void renderInit(GLFWwindow* window, Ecs* ecs);
void renderUpdate(Ecs* ecs);

#endif