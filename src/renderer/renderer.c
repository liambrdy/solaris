#include "renderer.h"

renderer_core *renderer;

void InitializeRenderer(memory_arena *arena) {
    assert(!renderer);

    renderer = ArenaPushStruct(arena, renderer_core);
    renderer->permenantArena = InitializeMemoryArena(1024 * 1024 * 10);
}