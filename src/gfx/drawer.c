#include "drawer.h"
#include "../state.h"
#include <math.h>

void draw_circle(float cx, float cy, float r, int num_segments, vec3 color) {

    glColor3f(color.x, color.y, color.z); 
    float aspect_ratio = (float)state.window->width / (float)state.window->height;
    float adjusted_radius = r * aspect_ratio; 

    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * M_PI * (float)ii / (float)num_segments; 
        float x = adjusted_radius * cosf(theta); 
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void draw_rect(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
