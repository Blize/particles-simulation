#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>

typedef void (*FDraw)();

typedef void (*FDrawCircle)(float cx, float cy, float r, int num_segments);
typedef void (*FDrawRect)(float x, float y, float w, float h);

enum CameraType {
    CAMERA_2D,
    CAMERA_3D,
};

struct Render {
    enum CameraType camera_type;
    FDrawCircle draw_circle;
    FDrawRect draw_rect;
};

extern struct Render render;

void init_renderer();

#endif
