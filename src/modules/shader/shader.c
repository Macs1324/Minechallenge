#ifndef SHADER_C
#define SHADER_C

#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include <GL/glew.h>

char* readShader(const char* filename)
{
    char *source = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1) { /* Error */ }

            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }
    else
    {
        printf("Cannot open file %s\n", filename);
    }

    return source;
}

Shader shaderCreateFromSource(const char* vertexShaderSrcFilename, const char* fragmentShaderSrcFilename)
{
    
    char* vertexShaderSrc = readShader(vertexShaderSrcFilename);
    char* fragmentShaderSrc = readShader(fragmentShaderSrcFilename);

    char* vertexShaderSrcPointer = vertexShaderSrc;
    char* fragmentShaderSrcPointer = fragmentShaderSrc;

    Shader r;
    unsigned int vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, (const GLchar * const*)&vertexShaderSrcPointer, NULL);
    glShaderSource(fs, 1, (const GLchar * const*)&fragmentShaderSrcPointer, NULL);


    glCompileShader(vs);
    unsigned int success;
    char infolog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        printf("Can't compile vertex shader!\n");
        glGetShaderInfoLog(vs, 512, NULL, infolog);
        printf("%s\n", infolog);
    }

    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        printf("Can't compile fragment shader!\n");
        glGetShaderInfoLog(fs, 512, NULL, infolog);
        printf("%s\n", infolog);
    }

    r.program = glCreateProgram();
    glAttachShader(r.program, vs);
    glAttachShader(r.program, fs);
    glLinkProgram(r.program);

    glGetProgramiv(r.program, GL_LINK_STATUS, &success);
    if(!success)
    {
        printf("Failed to link shader program!\n");
        glGetProgramInfoLog(r.program, 512, NULL, infolog);
        printf("%s\n", infolog);
    }

    // free(vertexShaderSrc);
    // free(fragmentShaderSrc);

    return r;
}

void shaderUse(Shader shader)
{
    glUseProgram(shader.program);
}

#endif