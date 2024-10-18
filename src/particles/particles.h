#ifndef PARTICLES_H
#define PARTICLES_H

#define GRAVITY 0.09f
#define COEFFICIENT_OF_RESTITUTION 0.95f 
#define PARTICLE_COUNT 100

#include <stdbool.h>

void init_particles();
void destroy_particles();

void did_particles_collide();
void update_particles();

#endif
