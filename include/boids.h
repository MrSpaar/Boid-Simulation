#ifndef BOIDS_BOIDS_H
#define BOIDS_BOIDS_H

#include "vectors.h"

#define WIDTH 1024
#define HEIGHT 720

typedef struct {
    vec2D pos;
    vec2D vel;
    vec2D acc;
    double strength;
} boid;

typedef struct {
    boid **list;
    int count;
} boid_list;

boid_list create_boid_list(int count);
void update_boid(boid *boid1, boid_list *boids);

#endif
