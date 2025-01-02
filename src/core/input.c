#include "input.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

input_state *input;

static key_type GLFWToKey(int key);
static button_type GLFWToButton(int button);

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    key_type code = GLFWToKey(key);

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (!input->keyDown[code]) {
            input->keyPressed[code] = true;
        }

        input->keyDown[code] = true;
    }
    else if (action == GLFW_RELEASE) {
        input->keyDown[code] = false;
        input->keyPressed[code] = false;
    }
}

void ButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    button_type code = GLFWToButton(button);

    if (action == GLFW_PRESS) {
        if (!input->buttonDown[code]) {
            input->buttonPressed[code] = true;
        }

        input->buttonDown[code] = true;
    } else if (action == GLFW_RELEASE) {
        input->buttonDown[code] = false;
        input->buttonPressed[code] = false;
    }
}


void InitializeInput(GLFWwindow *window, memory_arena *arena) {
    if (input) {
        UNREACHABLE;
    }

    input = ArenaPushStruct(arena, input_state);
    input->arena = arena;

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, ButtonCallback);
}

void InputUpdate() {
    memset(input->keyPressed, 0, KEY_COUNT * sizeof(b32));
    memset(input->buttonPressed, 0, BUTTON_COUNT * sizeof(b32));
}

static key_type GLFWToKey(int key) {
    switch (key) {
        case GLFW_KEY_A: return KEY_A;
        case GLFW_KEY_S: return KEY_S;
        case GLFW_KEY_D: return KEY_D;
        case GLFW_KEY_W: return KEY_W;
        case GLFW_KEY_SPACE: return KEY_SPACE;
    }

    return 0;
}

static button_type GLFWToButton(int button) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_1: return BUTTON_LEFT;
        case GLFW_MOUSE_BUTTON_2: return BUTTON_RIGHT;
        case GLFW_MOUSE_BUTTON_3: return BUTTON_MIDDLE;
        default: UNREACHABLE;
    }

    return BUTTON_COUNT;
}