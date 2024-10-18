#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "particles.h"
#include "../state.h"

void init_particles() {
    state.particle_count = PARTICLE_COUNT;
    state.particles = (struct Particle*)malloc(sizeof(struct Particle) * PARTICLE_COUNT);

    float radius = 15.0f;
    float spacing_x = 15.0f;  // Horizontal
    float spacing_y = 50.0f;  // Vertical

    int num_columns = ceil(sqrt(PARTICLE_COUNT)); 
    int num_rows = ceil((float)PARTICLE_COUNT / num_columns);
    float total_particle_width = num_columns * (2 * radius + spacing_x);
    float total_particle_height = num_rows * (2 * radius + spacing_y);

    float start_x = (state.window->width - total_particle_width) / 2.0f;
    float start_y = (state.window->height - total_particle_height) / 2.0f;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            int index = i * num_columns + j;
            if (index >= PARTICLE_COUNT) break;  // Prevent overflow

            // Introduce a horizontal offset for odd rows
            float offset_x = (i % 2 == 0) ? 0.0f : (radius + spacing_x / 2.0f);

            // Set particle position with the offset on every second row
            state.particles[index].position = (vec2){ 
                start_x + j * (2 * radius + spacing_x) + offset_x, 
                start_y + i * (2 * radius + spacing_y)
            };
            state.particles[index].velocity = (vec2){ 0.0f, 0.0f }; 
            state.particles[index].radius = radius;
            state.particles[index].active = true;
        }
    }
}

void destroy_particles() {
    free(state.particles);
}

void did_collide_with_box(struct Particle *particle) {
    // Horizontal collision
    if (particle->position.x - particle->radius < 0 || 
        particle->position.x + particle->radius > state.window->width) {
        particle->velocity.x = -particle->velocity.x * COEFFICIENT_OF_RESTITUTION;

        if (particle->position.x - particle->radius < 0) {
            particle->position.x = particle->radius;
        } else if (particle->position.x + particle->radius > state.window->width) {
            particle->position.x = state.window->width - particle->radius;
        }
    }

    // Vertical collision
    if (particle->position.y - particle->radius < 0 || 
        particle->position.y + particle->radius > state.window->height) {
        particle->velocity.y = -particle->velocity.y * COEFFICIENT_OF_RESTITUTION;

        if (particle->position.y - particle->radius < 0) {
            particle->position.y = particle->radius;
        } else if (particle->position.y + particle->radius > state.window->height) {
            particle->position.y = state.window->height - particle->radius;
        }
    }
}

void handle_particle_collision(struct Particle *p1, struct Particle *p2, float distance, float collision_distance, float dx, float dy) {

    // Calculate the current distance between particles
    vec2 current_position_diff = vec2_subtract(p1->position, p2->position);
    float current_distance = sqrt(dx * dx + dy * dy);

    // Resolve overlap
    if (current_distance < collision_distance) {
        float overlap = collision_distance - current_distance;
        vec2 overlap_vec = vec2_divide(current_position_diff, current_distance); 
        overlap_vec = vec2_multiply(overlap_vec, (vec2){overlap, overlap});

        p1->position = vec2_add(p1->position, vec2_divide(overlap_vec, 2.0f));  
        p2->position = vec2_subtract(p2->position, vec2_divide(overlap_vec, 2.0f)); 
    }

    vec2 normal = (vec2){dx / distance, dy / distance}; 
    vec2 tangent = (vec2){-normal.y, normal.x}; 

    float v1_normal = p1->velocity.x * normal.x + p1->velocity.y * normal.y;
    float v1_tangent = p1->velocity.x * tangent.x + p1->velocity.y * tangent.y;
    float v2_normal = p2->velocity.x * normal.x + p2->velocity.y * normal.y;
    float v2_tangent = p2->velocity.x * tangent.x + p2->velocity.y * tangent.y;

    // Calculate the new normal velocities based on elastic collision equations
    float v1_normal_new = (v1_normal * (p1->radius - p2->radius) + 2 * p2->radius * v2_normal) / (p1->radius + p2->radius);
    float v2_normal_new = (v2_normal * (p2->radius - p1->radius) + 2 * p1->radius * v1_normal) / (p1->radius + p2->radius);

    v1_normal_new *= COEFFICIENT_OF_RESTITUTION;
    v2_normal_new *= COEFFICIENT_OF_RESTITUTION;

    vec2 v1_normal_vec = (vec2){v1_normal_new * normal.x, v1_normal_new * normal.y};
    vec2 v1_tangent_vec = (vec2){v1_tangent * tangent.x, v1_tangent * tangent.y};
    vec2 v2_normal_vec = (vec2){v2_normal_new * normal.x, v2_normal_new * normal.y};
    vec2 v2_tangent_vec = (vec2){v2_tangent * tangent.x, v2_tangent * tangent.y};

    p1->velocity = vec2_add(v1_normal_vec, v1_tangent_vec);
    p2->velocity = vec2_add(v2_normal_vec, v2_tangent_vec);
}

/// If r1 + r2 >= distance between particles, then particles have collided
void did_particles_collide() {
    float collision_radius_scale = 1.5f; 

    for (int i = 0; i < state.particle_count; i++) {
        if (state.particles[i].active) {
            did_collide_with_box(&state.particles[i]);

            for (int j = i + 1; j < state.particle_count; j++) {
                if (state.particles[j].active) {

                    vec2 diff = vec2_subtract(state.particles[i].position, state.particles[j].position);
                    float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

                    // Detect collision using a scaled radius for early detection
                    float collision_distance = (state.particles[i].radius + state.particles[j].radius) * collision_radius_scale;

                    if (distance <= collision_distance) {
                        handle_particle_collision(&state.particles[i], &state.particles[j], distance, collision_distance, diff.x, diff.y);
                    }
                }
            }
        }
    }
}

void update_particles() {
    for (int i = 0; i < state.particle_count; i++) {
        if (state.particles[i].active) {
            state.particles[i].velocity.y -= GRAVITY; 
            state.particles[i].position = vec2_add(state.particles[i].position, state.particles[i].velocity);
        }
    }
}


