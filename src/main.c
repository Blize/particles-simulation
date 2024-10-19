#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "state.h"
#include "particles/particles.h"

// Global state variable
struct State state;

void init() {
    srand(time(NULL));
    init_particles();
    init_renderer();
}

void destroy() {
    destroy_particles();
    glfwTerminate();
}

void update() {
    printf("Frames: %llu\n", window.fps);
    if (!state.window->keyboard.keys[GLFW_KEY_SPACE].down) {
        update_particles();
        did_particles_collide();
    }
    if (state.window->keyboard.keys[GLFW_KEY_R].down) {
        destroy_particles();
        init_particles();
    }
    
}

void render_() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < state.particle_count; i++) {
        if (state.particles[i].active) {
            state.render->draw_circle(state.particles[i].position.x, state.particles[i].position.y, state.particles[i].radius, 100);
        }
    }
}

int main() {
    state.window = &window;
    state.render = &render;

    window_create(init, destroy, NULL, update, render_);
    window_loop();

    return 0;
}

