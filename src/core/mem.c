#include "mem.h"

#include <stdlib.h>
#include <assert.h>

typedef struct mem_state {
    u64 tagSizes[MEMORY_TAG_MAX];
} mem_state;

static mem_state *mem;

void *AllocMem(u64 size, memory_tag tag) {
    if (!mem) {
        mem = (mem_state *)malloc(sizeof(mem_state));
        assert(mem);
    }

    mem->tagSizes[tag] += size;

    void *block = malloc(size);
    assert(block);

    return block;
}

void FreeMem(void *block, u64 size, memory_tag tag) {
    assert(mem);

    mem->tagSizes[tag] -= size;

    free(block);
}

memory_arena *InitializeMemoryArena(u64 size) {
    memory_arena *arena = (memory_arena *)AllocMem(sizeof(memory_arena), MEMORY_TAG_ARENA);

    arena->memory = AllocMem(size, MEMORY_TAG_ARENA);
    arena->capacity = size;
    arena->allocated = 0;

    return arena;
}

void *ArenaPushBytes(memory_arena *arena, u64 size) {
    assert(arena);

    if (arena->allocated + size <= arena->capacity) {
        void *block = arena->memory;
        arena->memory += size;
        arena->allocated += size;

        return block;
    }

    assert(false && "Memory arena is full!");
    return NULL;
}

void ArenaFree(memory_arena *arena) {
    FreeMem(arena->memory, arena->capacity, MEMORY_TAG_ARENA);
    FreeMem(arena, sizeof(memory_arena), MEMORY_TAG_ARENA);
}

