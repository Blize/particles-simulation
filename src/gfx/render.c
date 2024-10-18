#include "render.h"
#include "drawer.h"
#include <OpenGL/gl.h>

#include "../state.h"

struct Render render;

void init_renderer() {
    render.draw_circle = draw_circle;
    render.draw_rect = draw_rect;
    render.camera_type = CAMERA_2D;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, state.window->width, state.window->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, state.window->width, 0, state.window->height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
