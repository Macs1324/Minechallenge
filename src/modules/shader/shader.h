#ifndef SHADER_H
#define SHADER_H

typedef struct
{
    unsigned int program;
}Shader;

char* readShader(const char* filename);
Shader shaderCreateFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc);
void shaderUse(Shader shader);

#endif