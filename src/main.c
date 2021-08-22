#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include <entity/components/transform.h>
#include <entity/entity.h>
#include <entity/ecs.h>
#include <entity/systems/render.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Sburo", NULL, NULL);

    glfwMakeContextCurrent(window);
    glewInit();
    Ecs world = ecsNew();
    EntityHandle block = ecsAddEntity(&world);

    float vertices[] = {
        0.5, 0.5,
        0.5, -0.5,
        -0.5, 0.5,
        -0.5, 0.5
    };
    world.mesh[0] = meshNew();
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.7, 1.0, 1.0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
} 