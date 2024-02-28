#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/boids.h"


void add_boid(boid_list_t *boids, boid_t *boid) {
    boid_t *tmp = (boid_t*) realloc(boids->list, (boids->count + 1) * sizeof(boid_t));

    if (tmp == NULL) {
        printf("Error: realloc failed\n");
        exit(1);
    }

    boids->list = tmp;
    boids->list[boids->count] = *boid;
    boids->count++;
}

boid_list_t create_boid_list(int count) {
    srand(time(NULL));
    boid_list_t boids = {calloc(count, sizeof(boid_t)), count};

    for (int i = 0; i < count; i++) {
        boids.list[i].pos.x = rand() % 1024;
        boids.list[i].pos.y = rand() % 720;
        boids.list[i].strength = 0;
    }

    return boids;
}

boid_list_t get_neighbours(boid_list_t *boids, boid_t *boid1, double radius) {
    boid_list_t neighbours = {calloc(1, sizeof(boid_t*)), 0};

    for (int i = 0; i < boids->count; i++) {
        double distance = dist(&boid1->pos, &boids->list[i].pos);

        if (distance < radius && distance != 0)
            add_boid(&neighbours, &boids->list[i]);
    }

    return neighbours;
}

vec2D compute_separation(boid_t *boid1, boid_list_t *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++) {
        vec2D diff = static_sub_vec(&boid1->pos, &neighbours->list[i].pos);
        add_vec(&force, &diff);
    }

    mul_vec(&force, weight);
    return force;
}

vec2D compute_cohesion(boid_t *boid1, boid_list_t *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i].pos);
    div_vec(&force, neighbours->count);

    sub_vec(&force, &boid1->pos);
    mul_vec(&force, weight);

    return force;
}

vec2D compute_alignment(boid_list_t *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i].vel);
    div_vec(&force, neighbours->count);

    mul_vec(&force, weight);
    return force;
}

void limit_vel(boid_t *boid1, double max_vel) {
    double vel = norm(&boid1->vel);

    if (vel > max_vel)
        mul_vec(&boid1->vel, max_vel/vel);
}

void limit_pos(boid_t *b, int limit) {
    if (b->pos.x < limit && b->acc.x < 0 || b->pos.x > WIDTH - limit && b->acc.x > 0)
        b->acc.x = -b->acc.x;

    if (b->pos.y < limit && b->acc.y < 0 || b->pos.y > HEIGHT - limit && b->acc.y > 0)
        b->acc.y = -b->acc.y;
}

void update_boid(boid_t *boid, boid_list_t *boids) {
    boid_list_t close = get_neighbours(boids, boid, 20);
    boid_list_t around = get_neighbours(boids, boid, 100);

    if (close.count > 0) {
        vec2D separation = compute_separation(boid, &close, 0.2);
        add_vec(&boid->acc, &separation);
    }

    if (around.count > 0) {
        vec2D cohesion = compute_cohesion(boid, &around, 0.5);
        vec2D alignment = compute_alignment(&around, 5);

        add_vec(&boid->acc, &cohesion);
        add_vec(&boid->acc, &alignment);
    }

    add_vec(&boid->vel, &boid->acc);
    limit_vel(boid, 2);
    limit_pos(boid, 20);
    add_vec(&boid->pos, &boid->vel);

    free(close.list);
    free(around.list);
}
