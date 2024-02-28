#include <stdlib.h>
#include "../include/boids.h"

boid_list_t *get_neighbours(boid_list_t *boids, boid_t *boid1, double radius) {
    boid_list_t *neighbours = calloc(sizeof(boid_list_t), 1);

    for (int i = 0; i < boids->count; i++) {
        double distance = dist(&boid1->pos, &boids->list[i].pos);

        if (distance < radius && distance != 0) {
            neighbours->count++;
            boid_t *temp = realloc(neighbours->list, neighbours->count*sizeof(boid_t));

            if (temp == NULL) {
                free(boids->list);
                free(boids);
                return NULL;
            }

            neighbours->list = temp;
            neighbours->list[neighbours->count-1] = boids->list[i];
        }
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

int update_boid(boid_t *boid, boid_list_t *boids) {
    boid_list_t *around = get_neighbours(boids, boid, 100);
    if (around == NULL) {
        return 1;
    }

    boid_list_t *close = get_neighbours(around, boid, 20);
    if (close == NULL) {
        return 1;
    }

    if (close->count > 0) {
        vec2D separation = compute_separation(boid, close, 0.2);
        add_vec(&boid->acc, &separation);
    }

    if (around->count > 0) {
        vec2D cohesion = compute_cohesion(boid, around, 0.5);
        vec2D alignment = compute_alignment(around, 5);

        add_vec(&boid->acc, &cohesion);
        add_vec(&boid->acc, &alignment);
    }

    add_vec(&boid->vel, &boid->acc);
    limit_vel(boid, 2);
    limit_pos(boid, 20);
    add_vec(&boid->pos, &boid->vel);

    free(close->list);
    free(around->list);

    free(close);
    free(around);

    return 0;
}
