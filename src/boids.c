#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "boids.h"

boid_list create_boid_list(int count) {
    srand(time(NULL));
    boid_list boids = {malloc(sizeof(boid*)*(count+1)), count};

    for (int i = 0; i < count; i++) {
        boids.list[i] = malloc(sizeof(boid));
        boids.list[i]->pos.x = rand() % 1024;
        boids.list[i]->pos.y = rand() % 720;
        boids.list[i]->strength = 0;

        if (!(rand()%100))
            boids.list[i]->strength = fmin(2, rand() % 5);
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

vec2D compute_separation(boid *boid1, boid_list *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++) {
        vec2D diff = static_sub_vec(&boid1->pos, &neighbours->list[i]->pos);
        add_vec(&force, &diff);
    }

    mul_vec(&force, weight);
    return force;
}

vec2D compute_cohesion(boid *boid1, boid_list *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i]->pos);
    div_vec(&force, neighbours->count);

    sub_vec(&force, &boid1->pos);
    mul_vec(&force, weight);

    return force;
}

vec2D compute_alignment(boid_list *neighbours, double weight) {
    vec2D force = {0, 0};

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i]->vel);
    div_vec(&force, neighbours->count);

    mul_vec(&force, weight);
    return force;
}

vec2D compute_leadership(boid *boid1, boid_list *neighbours, double weight) {
    boid *leader = neighbours->list[0];

    for (int i = 1; i < neighbours->count; i++)
        if (neighbours->list[i]->strength > leader->strength)
            leader = neighbours->list[i];

    if (leader->strength < 2)
        return (vec2D) {0, 0};

    vec2D force = {leader->pos.x - boid1->pos.x, leader->pos.y - boid1->pos.y};
    mul_vec(&force, leader->strength);

    mul_vec(&force, weight);
    return force;
}

void limit_vel(boid *boid1, double max_vel) {
    double vel = norm(&boid1->vel);

    if (vel > max_vel)
        mul_vec(&boid1->vel, max_vel/vel);
}

void limit_pos(boid *b, int limit) {
    if (b->pos.x < limit && b->acc.x < 0 || b->pos.x > WIDTH - limit && b->acc.x > 0)
        b->acc.x = -b->acc.x;

    if (b->pos.y < limit && b->acc.y < 0 || b->pos.y > HEIGHT - limit && b->acc.y > 0)
        b->acc.y = -b->acc.y;
}

void update_boid(boid *boid1, boid_list *boids) {
    boid_list close = get_neighbours(boids, boid1, 20);
    boid_list around = get_neighbours(boids, boid1, 100);

    if (close.count > 0) {
        vec2D separation = compute_separation(boid1, &close, 0.2);
        add_vec(&boid1->acc, &separation);
    }

    if (around.count > 0) {
        vec2D cohesion = compute_cohesion(boid1, &around, 0.5);
        vec2D alignment = compute_alignment(&around, 5);
        vec2D leadership = compute_leadership(boid1, &around, 1);

        add_vec(&boid1->acc, &cohesion);
        add_vec(&boid1->acc, &alignment);
        add_vec(&boid1->acc, &leadership);
    }

    add_vec(&boid1->vel, &boid1->acc);

    limit_vel(boid1, 2);
    limit_pos(boid1, 20);

    add_vec(&boid1->pos, &boid1->vel);
}