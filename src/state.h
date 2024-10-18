#ifndef STATE_H
#define STATE_H

#include "gfx/window.h"
#include "gfx/render.h"

struct Particle {
  vec2 position;
  vec2 velocity;
  float radius;
  bool active;
};

struct State {
  struct Window *window;
  struct Render *render;
  struct Particle *particles;
  int particle_count;
};

extern struct State state;

#endif

