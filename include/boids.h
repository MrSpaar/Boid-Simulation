#ifndef __BOIDS_BOIDS_H
#define __BOIDS_BOIDS_H

#include "vectors.h"

#define WIDTH 1024
#define HEIGHT 720
#define BOID_COUNT 300

typedef struct {
    vec2D pos;
    vec2D vel;
    vec2D acc;
    double strength;
} boid_t;

typedef struct {
    boid_t *list;
    int count;
} boid_list_t;

int update_boid(boid_t *boid, boid_list_t *boids);

#endif // __BOIDS_BOIDS_H
