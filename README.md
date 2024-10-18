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

## How do we simulate particle movement?

All the following steps are looking maybe more complicated than they are. This is more for me to recap and also learn a bit of latex.
The code of the funcitons I will be talking about can be found here: [particle.c](src/[particles/particles.c)

Base variables you should now:

```c
#define GRAVITY 0.09f
#define COEFFICIENT_OF_RESTITUTION 0.95f
#define PARTICLE_COUNT 100

struct Particle {
  vec2 position;
  vec2 velocity;
  float radius;
  bool active;
};
```

### How do we detect collisions?

To check for a collision between two particles, we first compute the vector difference between their positions:

$$
\text{diff} = \mathbf{p}_i - \mathbf{p}_j
$$

Next, we calculate the distance between the particles:

$$
\text{distance} = \sqrt{\text{diff}_x^2 + \text{diff}_y^2}
$$

To determine if a collision occurs, we compare the distance to the scaled sum of their radii:

_(We added a ***collision_radius_scale*** to make the collision detection more responsive. If we wouldn't have this the particles would react later than I wont them to)_

$$
\text{collision\_distance} = (r_i + r_j) \cdot \text{collision\_radius\_scale}
$$

A collision is detected if:

$$
\text{distance} \leq \text{collision\_distance}
$$

### How do we handle particle collisions?

When two particles collide, we need to resolve their positions and velocities. The following steps outline the mathematical process involved:

1. **Calculate the current position difference between the particles:**

   We compute the vector difference between the positions of the two particles:

   $$
   \text{diff} = \mathbf{p}_1 - \mathbf{p}_2
   $$

2. **Determine the current distance between the particles:**

   The distance can be calculated using the Euclidean formula:

   $$
   \text{current\_distance} = \sqrt{dx^2 + dy^2}
   $$

   where \(dx\) and \(dy\) are the differences in the x and y coordinates of the particles, respectively.

3. **Resolve overlap if a collision has occurred:**

   If the current distance is less than the collision distance, we have an overlap, which can be defined as:

   $$
   \text{overlap} = \text{collision\_distance} - \text{current\_distance}
   $$

   We then normalize the overlap vector and adjust the positions of both particles:

   $$
   \text{overlap\_vec} = \text{normalize}(\text{diff}) \cdot \text{overlap}
   $$

   Finally, we update the positions:

   $$
   \mathbf{p}_1 = \mathbf{p}_1 + \frac{\text{overlap\_vec}}{2}
   $$

   $$
   \mathbf{p}_2 = \mathbf{p}_2 - \frac{\text{overlap\_vec}}{2}
   $$

4. **Calculate the collision normals:**

   The normal vector, which indicates the direction of the collision, is calculated as:

   $$
   \mathbf{n} = \left( \frac{dx}{\text{distance}}, \frac{dy}{\text{distance}} \right)
   $$

   The tangent vector can be computed as:

   $$
   \mathbf{t} = \left( -n_y, n_x \right)
   $$

5. **Determine the normal and tangent velocities:**

   We can find the velocities in the normal and tangent directions for both particles:

   $$
   v_{1, \text{normal}} = \mathbf{v}_1 \cdot \mathbf{n}
   $$

   $$
   v_{1, \text{tangent}} = \mathbf{v}_1 \cdot \mathbf{t}
   $$

   $$
   v_{2, \text{normal}} = \mathbf{v}_2 \cdot \mathbf{n}
   $$

   $$
   v_{2, \text{tangent}} = \mathbf{v}_2 \cdot \mathbf{t}
   $$

6. **Calculate the new normal velocities based on the elastic collision equations:**

   Using the conservation of momentum, we calculate the new normal velocities:

   $$
   v_{1, \text{normal}}^{\text{new}} = \frac{v_{1, \text{normal}} \cdot (r_1 - r_2) + 2 \cdot r_2 \cdot v_{2, \text{normal}}}{r_1 + r_2}
   $$

   $$
   v_{2, \text{normal}}^{\text{new}} = \frac{v_{2, \text{normal}} \cdot (r_2 - r_1) + 2 \cdot r_1 \cdot v_{1, \text{normal}}}{r_1 + r_2}
   $$

   Each normal velocity is then scaled by the coefficient of restitution:

   $$
   v_{1, \text{normal}}^{\text{new}} \leftarrow v_{1, \text{normal}}^{\text{new}} \cdot \text{COEFFICIENT\_OF\_RESTITUTION}
   $$

   $$
   v_{2, \text{normal}}^{\text{new}} \leftarrow v_{2, \text{normal}}^{\text{new}} \cdot \text{COEFFICIENT\_OF\_RESTITUTION}
   $$

7. **Update the velocities of both particles:**

   Finally, we compute the new velocity vectors by combining the normal and tangent components:

   $$
   \mathbf{v}_1 = \mathbf{v}_{1, \text{normal}}^{\text{new}} \cdot \mathbf{n} + v_{1, \text{tangent}} \cdot \mathbf{t}
   $$

   $$
   \mathbf{v}_2 = \mathbf{v}_{2, \text{normal}}^{\text{new}} \cdot \mathbf{n} + v_{2, \text{tangent}} \cdot \mathbf{t}
   $$

By following these steps, we ensure that particles respond appropriately to collisions while conserving momentum and energy according to the principles of physics.

## Future improvements

- Implement a more efficient collision detection algorithm, such as a quadtree or spatial hashing, to reduce the number of pairwise comparisons.
- Add more complex particle interactions, such as friction, air resistance, and particle rotation.
