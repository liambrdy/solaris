#ifndef _MODEL_H
#define _MODEL_H

#include "core.h"
#include "buffer.h"

#include "core/maths.h"

typedef struct model {
    u32 handle;

    buffer *vertex;
    buffer *index;

    u32 vertexCount;
    u32 indexCount;
} model;

typedef struct vert_3d {
    vec3 position;
    vec3 color;
} vert_3d;

model *LoadModel(vert_3d *vertices, u32 vertexCount, u32 *indices, u32 indexCount);
void FreeModel(model *m);

#endif