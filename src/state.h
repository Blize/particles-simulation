#ifndef STATE_H
#define STATE_H

#include "gfx/window.h"
#include "gfx/render.h"
#include "util/util.h"

struct Particle {
  vec2 position;
  vec2 velocity;
  float radius;
  // color based on velocity
  vec3 color;
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

