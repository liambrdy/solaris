#ifndef _SHADER_H
#define _SHADER_H

#include "core.h"

typedef struct shader {
    u32 handle;
} shader;

shader *LoadShader(char *vertPath, char *fragPath, char *compPath);
void DestroyShader(shader *shad);

#endif