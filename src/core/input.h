#ifndef _INPUT_H
#define _INPUT_H

#include <GLFW/glfw3.h>

#include "core.h"
#include "mem.h"

typedef enum key_type {
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_W,
    KEY_SPACE,
    KEY_COUNT
} key_type;

typedef enum button_type {
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_MIDDLE,
    BUTTON_COUNT,
} button_type;

typedef struct input_state {
    b32 keyDown[KEY_COUNT];
    b32 keyPressed[KEY_COUNT];

    b32 buttonDown[BUTTON_COUNT];
    b32 buttonPressed[BUTTON_COUNT];

    memory_arena *arena;
} input_state;

extern input_state *input;

void InitializeInput(GLFWwindow *window, memory_arena *arena);
void InputUpdate();

#endif