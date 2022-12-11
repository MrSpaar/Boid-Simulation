#ifndef BOIDS_BOIDS_H
#define BOIDS_BOIDS_H

#include "vectors.h"

typedef struct {
    vec2D pos;
    vec2D vel;
    vec2D acc;
} boid;

typedef struct {
    boid **list;
    int count;
} boid_list;

boid_list create_boid_list(int count);
boid_list get_neighbours(boid_list *boids, boid *boid1, double radius);

#endif
