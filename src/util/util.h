#ifndef UTIL_H
#define UTIL_H

typedef struct vec2 {
    float x, y;
} vec2;

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct vec4 {
    float x, y, z, w;
} vec4;

vec2 vec2_multiply(vec2 a, vec2 b);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_divide(vec2 a, float b);
vec2 vec2_subtract(vec2 a, vec2 b);
float clamp(float x, float mn, float mx);

#endif

