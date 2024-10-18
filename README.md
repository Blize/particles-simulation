# Partical Simulation

## Introduction

This is a simple project I did in C. It is probably not scientifically accurate, but it was fun to make. The program simulates the movement of particles in a 2D space.
The particles are affected by gravity and can collide with each other. The program uses the GLFW library to display the particles on the screen, the rest is fully coded by me.

## How to install

### Unix

1. Clone the repository

```
git clone https://github.com/Blize/Particle-Simulation.git
```

2. Install the GLFW library

```bash
sudo apt-get install libglfw3
```

or

```bash
brew install glfw
```

3. Build the project

```bash
 cd build
```

```bash
cmake ..
```

```bash
make
```

```bash
./engine
```

### Windows

Good luck! I have no idea how to install the GLFW library on Windows.

## How does it work?

If you wanna understand how I strucutred the engine I would suggest you start in the [main.c](src/main.c) file. From there follow the
`init()` function. After that go through the `update()` function and finally the `render()` function.

Also intresting to see is how we handle the States. For that we have the [state.h](src/state.h) file. Via that we have globally access
to our states and header files.

For the Math behind the simulation have a look at the [Math](Math.pdf) file.

## Future improvements

- Implement a more efficient collision detection algorithm, such as a quadtree or spatial hashing, to reduce the number of pairwise comparisons.
- Add more complex particle interactions, such as friction, air resistance, and particle rotation.
