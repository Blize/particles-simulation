#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdbool.h>

#include "../util/util.h"

struct Button {
    bool down, last, last_tick, pressed, pressed_tick;
};

struct Mouse {
    struct Button buttons[GLFW_MOUSE_BUTTON_LAST];
    vec2 position, delta;
};

struct Keyboard {
    struct Button keys[GLFW_KEY_LAST];
};

// Function pointer type for window callbacks
typedef void (*FWindow)();

struct Window {
    GLFWwindow *handle;
    int width;       
    int height;
    FWindow init, destroy, tick, update, render; // Callbacks for handling window events
    struct Mouse mouse;
    struct Keyboard keyboard;

    // Timing variables
    uint64_t last_second;
    uint64_t frames, fps, last_frame, frame_delta;
    uint64_t ticks, tps, tick_remainder;
};

// Global window instance
extern struct Window window;

void window_loop(); 
void window_create(FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render);
void mouse_set_grabbed(bool grabbed);
bool mouse_get_grabbed();

#endif

