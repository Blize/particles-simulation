#include "window.h"
#include <stdio.h>

// Global window variable
struct Window window;

static void _init() {
    if (window.init) {
        window.init();
    }
}

static void _destroy() {
    if (window.destroy) {
        window.destroy();
    }
}

static void _update() {
    if (window.update) {
        window.update();
    }
}

static void _render() {
    if (window.render) {
        window.render();
    }
}

static void key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
    if (key < 0) {
        return;
    }

    switch (action) {
        case GLFW_PRESS:
            window.keyboard.keys[key].down = true;
            break;
        case GLFW_RELEASE:
            window.keyboard.keys[key].down = false;
            break;
        default:
            break;
    }
}

static void mouse_callback(GLFWwindow *handle, int button, int action, int mods) {
    if (button < 0) {
        return;
    }

    switch (action) {
        case GLFW_PRESS:
            window.mouse.buttons[button].down = true;
            break;
        case GLFW_RELEASE:
            window.mouse.buttons[button].down = false;
            break;
        default:
            break;
    }
}

static void cursor_callback(GLFWwindow *handle, double xp, double yp) {
    vec2 p = {xp, yp};

    window.mouse.delta = vec2_subtract(p, window.mouse.position);
    window.mouse.delta.x = clamp(window.mouse.delta.x, -100.0f, 100.0f);
    window.mouse.delta.y = clamp(window.mouse.delta.y, -100.0f, 100.0f);


    window.mouse.position = p;
}

static void handle_error_callback(int code, const char* description) {
    // GLenum err;
    // while ((err = glGetError()) != GL_NO_ERROR) {
    //     printf("OpenGL error: %d\n", err);
    // }
    printf("Error code & description: %d, %s\n", code, description);
    _destroy();
}

void framebuffer_size_callback(GLFWwindow* handle, int width, int height) {
    window.width = width;
    window.height = height;
    glViewport(0, 0, width, height);
}

void window_create(FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render) {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return;
    }
  
    window.width = 1500; 
    window.height = 1200;
    window.handle = glfwCreateWindow(window.width, window.height, "Engine", NULL, NULL);
    
    if (!window.handle) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window.handle);
    
    // Set window hints for OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Ensure double buffering is enabled
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    glfwSetKeyCallback(window.handle, key_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_callback);
    glfwSetCursorPosCallback(window.handle, cursor_callback);
    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetErrorCallback(handle_error_callback);

    glfwSwapInterval(1);

    // Set the window callbacks
    window.init = init;
    window.destroy = destroy;
    window.update = update;
    window.render = render;

    _init();
}

void window_loop() {
    window.frames = 0;
    window.ticks = 0;
    window.last_second = glfwGetTime();

    while (!glfwWindowShouldClose(window.handle) && !window.keyboard.keys[GLFW_KEY_ESCAPE].down) {
        window.ticks++;
        window.frames++; 
        uint64_t now = glfwGetTime();

        if (now - window.last_second >= 1.0) {
            window.fps = window.frames;
            window.tps = window.ticks;
            window.frames = 0;
            window.ticks = 0;
            window.last_second = now;
        }

        _update();
        _render();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    _destroy(); 
}

void mouse_set_grabbed(bool grabbed) {
    glfwSetInputMode(window.handle, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool mouse_get_grabbed() {
    return glfwGetInputMode(window.handle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}
