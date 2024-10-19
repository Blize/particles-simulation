#include "util.h"

vec2 vec2_multiply(vec2 a, vec2 b) {
    return (vec2) {a.x * b.x, a.y * b.y};
}

vec2 vec2_add(vec2 a, vec2 b) {
    return (vec2) {a.x + b.x, a.y + b.y};
}

vec2 vec2_divide(vec2 a, float b) {
    if (b == 0) return a;
    return (vec2) {a.x / b, a.y / b};
}

vec2 vec2_subtract(vec2 a, vec2 b) {
    return (vec2) {a.x - b.x, a.y - b.y};
}

float clamp(float x, float mn, float mx) {
    if (x < mn) return mn;
    if (x > mx) return mx;
    return x;
}
