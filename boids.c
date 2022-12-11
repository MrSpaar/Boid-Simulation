#include "boids.h"
#include <malloc.h>
#include <stdlib.h>

boid_list create_boid_list(int count) {
    boid_list boids = {malloc(sizeof(boid*)*(count+1)), count};

    for (int i = 0; i < count; i++) {
        boids.list[i] = malloc(sizeof(boid));
        boids.list[i]->pos.x = rand() % 1024;
        boids.list[i]->pos.y = rand() % 720;
    }

    return boids;
}

boid_list get_neighbours(boid_list *boids, boid *boid1, double radius) {
    boid_list neighbours = {NULL, 0};

    for (int i = 0; i < boids->count; i++) {
        double distance = dist(&boid1->pos, &boids->list[i]->pos);

        if (distance < radius && distance != 0) {
            neighbours.list = realloc(neighbours.list, sizeof(boid*) * (neighbours.count+1));
            neighbours.list[neighbours.count] = boids->list[i];
            neighbours.count++;
        }
    }
    return neighbours;
}
