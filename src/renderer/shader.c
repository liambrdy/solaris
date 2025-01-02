#include "shader.h"

#include <stdio.h>

#include "core/mem.h"
#include "renderer.h"

#include <glad/gl.h>

static char *ReadFile(char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Failed to read file: %s\n", path);
        UNREACHABLE;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = AllocMem(size + 1, MEMORY_TAG_TEMP);

    size_t read = fread(buf, sizeof(char), size, f);
    assert(read == size);

    buf[size] = '\0';

    fclose(f);

    return buf;
}

static GLuint CreateShader(char *code, GLenum type) {
    GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, (const char **)&code, NULL);
    glCompileShader(handle);

    i32 status = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infoLog[1024];
        glGetShaderInfoLog(handle, 1024, NULL, infoLog);

        printf("Failed to compile shader:\n%s\n", infoLog);
        UNREACHABLE;
    }

    return handle;
}

shader *LoadShader(char *vertPath, char *fragPath, char *compPath) {
    shader *shad = ArenaPushStruct(renderer->permenantArena, shader);
    shad->handle = glCreateProgram();

    if (vertPath && fragPath) {
        char *vertCode = ReadFile(vertPath);
        char *fragCode = ReadFile(fragPath);

        GLuint vert = CreateShader(vertCode, GL_VERTEX_SHADER);
        GLuint frag = CreateShader(fragCode, GL_FRAGMENT_SHADER);

        glAttachShader(shad->handle, vert);
        glAttachShader(shad->handle, frag);

        FreeMem(vertCode, 0, MEMORY_TAG_TEMP);
        FreeMem(fragCode, 0, MEMORY_TAG_TEMP);
    } else if (compPath) {
        char *compCode = ReadFile(compPath);
        GLuint comp = CreateShader(compCode, GL_COMPUTE_SHADER);
        glAttachShader(shad->handle, comp);

        FreeMem(compCode, 0, MEMORY_TAG_TEMP);
    }

    glLinkProgram(shad->handle);

    i32 status = 0;
    glGetProgramiv(shad->handle, GL_LINK_STATUS, &status);
    if (!status) {
        char infoLog[1024];
        glGetProgramInfoLog(shad->handle, 1024, NULL, infoLog);

        printf("Failed to link program:\n%s\n", infoLog);
        UNREACHABLE;
    }

    return shad;
}

void DestroyShader(shader *shad) {
    glDeleteProgram(shad->handle);
}