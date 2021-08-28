#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 fUv;

void main()
{
    fUv = vUv;
    gl_Position = proj * view * model * vec4(vPos, 1.0);
}