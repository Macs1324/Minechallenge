#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUv;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 fUv;
out vec3 fNormal;
out vec3 fPos;

void main()
{
    fUv = vUv;
    fNormal = normal;
    gl_Position = proj * view * model * vec4(vPos, 1.0);
    fPos = vec3(gl_Position);
}
