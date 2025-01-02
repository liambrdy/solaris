#ifndef _MEMORY_H
#define _MEMORY_H

#include "core.h"

typedef enum memory_tag {
    MEMORY_TAG_ARENA,
    MEMORY_TAG_TEMP,
    MEMORY_TAG_MAX,
} memory_tag;

void *AllocMem(u64 size, memory_tag tag);
void FreeMem(void *block, u64 size, memory_tag tag);

typedef struct memory_arena {
    void *memory;
    u64 capacity;
    u64 allocated;
} memory_arena;

memory_arena *InitializeMemoryArena(u64 size);
void *ArenaPushBytes(memory_arena *arena, u64 size);
void ArenaFree(memory_arena *arena);

#define ArenaPushStruct(arena, type) ArenaPushBytes(arena, sizeof(type))
#define ArenaPushArray(arena, type, count) ArenaPushBytes(arena, count * sizeof(type))

#endif