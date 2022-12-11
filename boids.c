#include <malloc.h>
#include "boids.h"

boid_list get_neighbours(boid_list *boids, boid *boid1, double radius) {
    boid_list neighbours = {NULL, 0};

    for (int i = 0; i < boids->count; i++) {
        double distance = dist(&boid1->pos, &boids->boids[i]->pos);

        if (distance < radius && distance != 0) {
            neighbours.boids = realloc(neighbours.boids, sizeof(boid*) * (neighbours.count+1));
            neighbours.boids[neighbours.count] = boids->boids[i];
            neighbours.count++;
        }
    }
    return neighbours;
}
