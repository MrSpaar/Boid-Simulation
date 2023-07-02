#ifndef BOIDS_BOIDS_H
#define BOIDS_BOIDS_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "vectors.h"


#define WIDTH 1024
#define HEIGHT 720

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


boid_list_t create_boid_list(int count);
void update_boid(boid_t *boid, boid_list_t *boids);


inline void add_boid(boid_list_t *boids, boid_t *boid) {
    boid_t *tmp = realloc(boids->list, (boids->count + 1) * sizeof(boid_t));

    if (tmp == NULL) {
        printf("Error: realloc failed\n");
        exit(1);
    }

    boids->list = tmp;
    boids->list[boids->count] = *boid;
    boids->count++;
}

#endif
