# Boid Simulation

This is an extended implementation of Reynolds' Boids algorithm in C using SDL.<br>
Boid's flocking behaviour is simulated using a simple rule-based system :
- Cohesion : Boids try to stay close to local flockmates.<br>
  ![Separation force](./images/coh.svg)
- Separation : Boids try to avoid crowding local flockmates.<br>
![Separation force](./images/sep.svg)
- Alignment : Boids try to fly the same direction as local flockmates.<br>
![Separation force](./images/ali.svg)

Where :
- V is the set of boids in the neighbourhood of a boid.
- N is the number of boids in the neighbourhood of a boid.
- p, v and a are the position, velocity and acceleration vectors of a boid.

We can then apply coefficients to each rule to tune the flocking behaviour :<br>
![Separation force](./images/acc.svg)

Each frame, the boids are updated using the following formula :
- ![Separation force](./images/vel.svg)
- ![Separation force](./images/pos.svg)

Addionally, the boids are constrained to stay within the window and their speed is limited to a maximum value.