#ifndef _BUFFER_H
#define _BUFFER_H

#include "core.h"
#include "core/mem.h"

typedef enum buffer_type {
    BUFFER_TYPE_VERTEX,
    BUFFER_TYPE_INDEX,
    BUFFER_TYPE_COUNT,
} buffer_type;

typedef struct buffer {
    u32 handle;
    buffer_type type;
    u32 size;
} buffer;

buffer *InitializeBuffer(buffer_type type, u32 size, void *mem);
void DestroyBuffer(buffer *buf);

#endif