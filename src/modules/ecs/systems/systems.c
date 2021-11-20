#ifndef ECS_SYSTEMS_H
#define ECS_SYSTEMS_H

#include <ecs/ecs.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "systems.h"

void renderInit(GLFWwindow* window, Ecs* ecs)
{
    glEnable(GL_CULL_FACE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    ecs->data.meshShaderProgram = shaderCreateFromSource(
        "./res/shaders/mesh.vs",
        "./res/shaders/mesh.fs"
    );
}
void renderUpdate(Ecs* ecs)
{
    Entity cameraEntity = ecsGetMainCameraEntity(ecs);
    cCamera* cameraComponent = ecsGetComponent(ecs, cameraEntity, ECS_CAMERA);
    cTransform* cameraTransform = ((cTransform*)ecsGetComponent(ecs, cameraEntity, ECS_TRANSFORM));
    for(int i = 0; i < ecs->nrMesh; i++)
    {
        cMesh* mesh = &ecs->mesh[i];
        cTransform* transform = ecsGetComponent(ecs, mesh->data.parent, ECS_TRANSFORM);

        mat4 view;
        mat4 proj;
        mat4 model;

        vec3 lookat;
        lookat[0] = cos(glm_rad(cameraTransform->rotation[1])) * cos(glm_rad(cameraTransform->rotation[0]));
        lookat[2] = sin(glm_rad(cameraTransform->rotation[1])) * cos(glm_rad(cameraTransform->rotation[0]));
        lookat[1] = sin(glm_rad(cameraTransform->rotation[0]));
        glm_vec3_add(cameraTransform->position, lookat, lookat);

        glm_mat4_identity(model);
        glm_rotate(model, transform->rotation[0], (vec3){1.0, 0.0, 0.0});
        glm_rotate(model, transform->rotation[1], (vec3){0.0, 1.0, 0.0});
        glm_rotate(model, transform->rotation[2], (vec3){0.0, 0.0, 1.0});
        glm_scale(model, transform->scale);
        glm_translate(model, transform->position);

        glm_lookat_rh(
            cameraTransform->position,
            lookat,
            (vec3){0.0, 1.0, 0.0},
            view
            );


        glm_perspective(cameraComponent->fov, 
            ecs->data.screenWidth / ecs->data.screenHeight, 
            cameraComponent->clipNear, 
            cameraComponent->clipFar, 
            proj);

        glUseProgram(ecs->data.meshShaderProgram.program);
        glBindVertexArray(mesh->vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementArray);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->texture);
        glUniform1i(glGetUniformLocation(ecs->data.meshShaderProgram.program, "sprite"), 0);
        glUniformMatrix4fv(glGetUniformLocation(ecs->data.meshShaderProgram.program, "model"), 1, GL_FALSE, model);
        glUniformMatrix4fv(glGetUniformLocation(ecs->data.meshShaderProgram.program, "view"), 1, GL_FALSE, view);
        glUniformMatrix4fv(glGetUniformLocation(ecs->data.meshShaderProgram.program, "proj"), 1, GL_FALSE, proj);
        glDrawElements(GL_TRIANGLES, mesh->nrIndices, GL_UNSIGNED_INT, 0);
    }
}

#endif