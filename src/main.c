#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <ecs/ecs.h>
#include <ecs/systems/systems.h>
#include <shader/shader.h>
#include <ecs/systems/worldgen.h>

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

int prev_xpos = 400;
int prev_ypos = 400;


Ecs world;

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    double sens = 0.1;

    double xvel = xpos - prev_xpos;
    double yvel = ypos - prev_ypos;

    ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1] += xvel * sens;
    ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0] -= yvel * sens;

    ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0] = glm_clamp(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0], -80.0, 80.0);
    if(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1] > 360)
    {
        ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1] = 0;
    }
    if(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1] < 0)
    {
        ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1] = 360;
    }

    // printf("%f %f\n", ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0], ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1]);


    prev_xpos = xpos;
    prev_ypos = ypos;
}

void processInput(GLFWwindow *window, Ecs* ecs)
{
    vec3 velocity;
    glm_vec3_zero(velocity);
    const float cameraSpeed = 20.0f * ecs->data.timeDelta; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        velocity[2] += sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1]));
        velocity[0] += cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1]));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        velocity[2] -= sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1]));
        velocity[0] -= cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1]));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        vec3 lookat;
        lookat[0] = cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1])) * cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));
        lookat[2] = sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1])) * cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));
        lookat[1] = sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));

        glm_cross(lookat, (vec3){0.0, -1.0, 0.0}, lookat);

        glm_vec3_add(lookat, velocity, velocity);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        vec3 lookat;
        lookat[0] = cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1])) * cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));
        lookat[2] = sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[1])) * cos(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));
        lookat[1] = sin(glm_rad(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->rotation[0]));

        glm_cross(lookat, (vec3){0.0, 1.0, 0.0}, lookat);
        glm_vec3_add(lookat, velocity, velocity);

    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        velocity[1] += 1;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        velocity[1] -= 1;
    }

    if(velocity[0] != 0 || velocity[1] != 0 || velocity[2] != 0)
    {
        glm_normalize(velocity);
        glm_vec3_muladds(velocity, cameraSpeed, ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->position);
        // glm_vec3_add(((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->position, velocity, ((cTransform*)(ecsGetComponent(&world, ecsGetMainCameraEntity(&world), ECS_TRANSFORM)))->position);
    }
}



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lesbicraft", NULL, NULL);

    glfwMakeContextCurrent(window);
    glewInit();

    world = ecsNew();
    world.data.screenWidth = SCREEN_WIDTH;
    world.data.screenHeight = SCREEN_HEIGHT;


    Entity chunks[12*12];

    for(int i = 0; i < 12*12; i++)
    {
        chunks[i] = ecsAddEntity(&world);
        ecsAddComponent(&world, chunks[i], ECS_MESH);
        cMesh chunk;
        chunk = genChunk(&world, (vec2){i / 12, i % 12}, 16);
        cMeshLoadTexture(ecsGetComponent(&world, chunks[i], ECS_MESH), "./res/blocks/atlas.png");
        ((cMesh*)ecsGetComponent(&world, chunks[i], ECS_MESH))->vertexBuffer = chunk.vertexBuffer;
        ((cMesh*)ecsGetComponent(&world, chunks[i], ECS_MESH))->vertexArray = chunk.vertexArray;
        ((cMesh*)ecsGetComponent(&world, chunks[i], ECS_MESH))->nrIndices = chunk.nrIndices;
        ((cMesh*)ecsGetComponent(&world, chunks[i], ECS_MESH))->elementArray = chunk.elementArray;
    }

    Entity player = ecsAddEntity(&world);
    ((cTransform*)ecsGetComponent(&world, player, ECS_TRANSFORM))->rotation[1] = 90;
    ((cTransform*)ecsGetComponent(&world, player, ECS_TRANSFORM))->position[2] -= 20;
    ((cTransform*)ecsGetComponent(&world, player, ECS_TRANSFORM))->position[1] = 90;
    ecsAddComponent(&world, player, ECS_CAMERA);
    ecsSetMainCameraEntity(&world, player);


    renderInit(window, &world);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glfwSetCursorPosCallback(window, cursorCallback);
    float angle = 0;
    printf("%d\n", world.nrMesh);
    while(!glfwWindowShouldClose(window))
    {
        ecsFrameStart(&world);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3, 0.7, 1.0, 1.0);
        // ((cTransform*)ecsGetComponent(&world, block, ECS_TRANSFORM))->rotation[1] += 1 * world.data.timeDelta;
        processInput(window, &world);

        renderUpdate(&world);
        glfwPollEvents();
        glfwSwapBuffers(window);
        ecsFrameEnd(&world);
    }
}
