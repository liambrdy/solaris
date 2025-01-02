#include "model.h"

#include "renderer.h"

#include <glad/gl.h>

model *LoadModel(vert_3d *vertices, u32 vertexCount, u32 *indices, u32 indexCount) {
    model *m = ArenaPushStruct(renderer->permenantArena, model);

    glCreateVertexArrays(1, &m->handle);
    glBindVertexArray(m->handle);

    m->vertex = InitializeBuffer(BUFFER_TYPE_VERTEX, vertexCount * sizeof(vert_3d), vertices);
    m->index = InitializeBuffer(BUFFER_TYPE_INDEX, indexCount * sizeof(indices[0]), indices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (const void *)(3 * sizeof(f32)));

    m->indexCount = indexCount;
    m->vertexCount = vertexCount;

    return m;
}

void FreeModel(model *m) {
    DestroyBuffer(m->vertex);
    DestroyBuffer(m->index);
}