# Boid Simulation

This is an extended implementation of Reynolds' Boids algorithm in C using SDL.<br>
Boid's flocking behaviour is simulated using a simple rule-based system :
- Separation : Boids try to avoid crowding local flockmates.<br>
<img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{a_{sep}} = \sum_{b \in V}\overrightarrow{p}-\overrightarrow{p_b} "/><br>

- Alignment : Boids try to fly the same direction as local flockmates.<br>
 <img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{a_{ali}} = \frac{1}{N}\sum_{b \in V}\overrightarrow{v_b} "/><br>

- Cohesion : Boids try to stay close to local flockmates.<br>
<img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{a_{coh}} = \frac{1}{N}\sum_{b \in V}\overrightarrow{p_b} "/><br>

Where :
- V is the set of boids in the neighbourhood of a boid.
- N is the number of boids in the neighbourhood of a boid.
- p, v and a are the position, velocity and acceleration vectors of a boid.

We can then apply coefficients to each rule to tune the flocking behaviour :<br>
<img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{a}=p_{sep}\cdot\overrightarrow{a_{sep}}+p_{coh}\cdot\overrightarrow{a_{coh}}+p_{ali}\cdot\overrightarrow{a_{ali}}">

Each frame, the boids are updated using the following formula :
- <img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{v_{new}}=\overrightarrow{v_{old}}+\overrightarrow{a_{new}}"> <br>
- <img src="https://latex.codecogs.com/svg.latex?\color{White}\overrightarrow{p_{new}}=\overrightarrow{p_{old}}+\overrightarrow{v_{new}}">

Addionally, the boids are constrained to stay within the window and their speed is limited to a maximum value.