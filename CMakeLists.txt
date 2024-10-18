cmake_minimum_required(VERSION 3.0)
project(engine)

# Enable the generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Manually set GLFW paths based on Homebrew's installation
set(GLFW_INCLUDE_DIR "/usr/local/opt/glfw/include")
set(GLFW_LIBRARY_DIR "/usr/local/opt/glfw/lib")

include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

# Add executable
add_executable(engine 
  src/main.c
  src/gfx/window.c
  src/util/util.c
  src/gfx/render.c
  src/gfx/drawer.c
  src/particles/particles.c
)

# Link OpenGL and GLFW
target_link_libraries(engine
    ${OPENGL_LIBRARIES}
    glfw
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

