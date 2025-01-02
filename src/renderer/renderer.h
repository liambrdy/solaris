#ifndef _RENDERER_H
#define _RENDERER_H

#include "core.h"
#include "core/mem.h"

typedef struct renderer_core {
    memory_arena *permenantArena;
} renderer_core;

extern renderer_core *renderer;

void InitializeRenderer(memory_arena *arena);

#endif