# Boid Simulation

This is an extended implementation of Reynolds' Boids algorithm in C using SDL.
![Demo Video](images/demo.gif)

Boid's flocking behaviour is simulated using a simple rule-based system :
- **Cohesion :** Boids try to stay close to local flockmates.<br>
<img align="center" src="images/coh.svg">

- **Separation :** Boids try to avoid crowding local flockmates.<br>
<img align="center" src="images/sep.svg">

- **Alignment :** Boids try to fly the same direction as local flockmates.<br>
<img align="center" src="images/ali.svg">

Where :
- **V** is the set of boids in the neighbourhood of a boid.
- **N** is the number of boids in the neighbourhood of a boid.
- **p**, **v** and **a** are the position, velocity and acceleration vectors of a boid.

We can then apply coefficients to each rule to tune the flocking behaviour :<br>
<img align="center" src="images/acc.svg">

Each frame, the boids are updated using the following formula :<br>
<img align="center" src="images/vel.svg">
<img align="center" src="images/pos.svg">

## Additional features

Boid velocity is capped to a maximum value :<br>
<img align="center" src="images/vel_cap.svg">

If a boid is going towards a wall, it will be repelled by it (pseudo-code):
```py
if (Px < limit and Ax < 0) or (Px > width-limit and Ax > 0)
    Ax *= -1;

if (Py < limit and Ay < 0) or (Py > height-limit and Ay > 0)
    Ay *= -1;
```
