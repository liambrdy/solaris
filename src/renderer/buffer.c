#include "buffer.h"

#include <glad/gl.h>

#include "renderer.h"

static GLenum GetGLEnumBufferType(buffer_type type) {
    switch (type) {
        case BUFFER_TYPE_VERTEX: return GL_ARRAY_BUFFER;
        case BUFFER_TYPE_INDEX: return GL_ELEMENT_ARRAY_BUFFER;
        default: UNREACHABLE;
    }

    return 0;
}

buffer *InitializeBuffer(buffer_type type, u32 size, void *mem) {
    buffer *buf = ArenaPushStruct(renderer->permenantArena, buffer);

    GLenum enumType = GetGLEnumBufferType(type);

    glCreateBuffers(1, &buf->handle);
    glBindBuffer(enumType, buf->handle);
    glBufferData(enumType, size, mem, GL_STATIC_DRAW);
    
    buf->size = size;
    buf->type = enumType;

    return buf;
}

void DestroyBuffer(buffer *buf) {
    glDeleteBuffers(1, &buf->handle);
}
