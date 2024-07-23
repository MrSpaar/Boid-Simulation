# Boid Simulation

This is an extended implementation of Reynolds' Boids algorithm in C/C++ using SDL.
![Result Preview](images/demo.gif)

Boid's flocking behaviour is simulated using a simple rule-based system :
- **Cohesion :** Boids try to stay close to local flockmates.<br>
$$\vec{a_{coh}} = \frac{1}{N}\sum_{b \in V} \vec{p_b}$$

- **Separation :** Boids try to avoid crowding local flockmates.<br>
$$\vec{a_{sep}} = \sum_{b \in V}(\vec{p}-\vec{p_b})$$

- **Alignment :** Boids try to fly the same direction as local flockmates.<br>
$$\vec{a_{ali}} = \frac{1}{N}\sum_{b \in V}\vec{v_b}$$

Where :
- **V** is the set of boids in the neighbourhood of a boid.
- **N** is the number of boids in the neighbourhood of a boid.
- **p**, **v** and **a** are the position, velocity and acceleration vectors of a boid.

We can then apply coefficients to each rule to tune the flocking behaviour :<br>
$$\vec{a} = K_{sep}\cdot\vec{a_{sep}} + K_{coh}\cdot\vec{a_{coh}} + K_{ali}\cdot\vec{a_{ali}}$$

Each frame, the boids are updated using the following formula :<br>
$$\vec{v'} = \vec{v}+\vec{a}\text{ then }\vec{p'} = \vec{p}+\vec{v'}$$

## Additional features

Boid velocity is capped to a maximum value :
$$\vec{v_{lim}} = \frac{V_{max}}{|\vec{v}|}\vec{v}$$

If a boid is going towards a wall, it will be repelled by it (pseudo-code):
```py
if (Px < limit and Ax < 0) or (Px > width-limit and Ax > 0)
    Ax *= -DAMPING_FACTOR;

if (Py < limit and Ay < 0) or (Py > height-limit and Ay > 0)
    Ay *= -DAMPING_FACTOR;
```
