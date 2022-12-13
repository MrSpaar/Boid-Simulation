#include "boids.h"
#include <malloc.h>
#include <stdlib.h>

boid_list create_boid_list(int count) {
    boid_list boids = {malloc(sizeof(boid*)*(count+1)), count};

    for (int i = 0; i < count; i++) {
        boids.list[i] = malloc(sizeof(boid));
        boids.list[i]->pos.x = rand() % 1024;
        boids.list[i]->pos.y = rand() % 720;

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

vec2D compute_separation(boid *boid1, boid_list *neighbours) {
    vec2D force = {0, 0};

    if (neighbours->count == 0)
        return force;

    for (int i = 0; i < neighbours->count; i++) {
        vec2D diff = sub_vec(&boid1->pos, &neighbours->list[i]->pos);
        add_vec(&force, &diff);
    }

    return force;
}

vec2D compute_cohesion(boid *boid1, boid_list *neighbours) {
    vec2D force = {0, 0};

    if (neighbours->count == 0)
        return force;

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i]->pos);
    div_vec(&force, neighbours->count);

    return sub_vec(&force, &boid1->pos);
}

vec2D compute_alignment(boid_list *neighbours) {
    vec2D force = {0, 0};

    if (neighbours->count == 0)
        return force;

    for (int i = 0; i < neighbours->count; i++)
        add_vec(&force, &neighbours->list[i]->vel);
    div_vec(&force, neighbours->count);

    return force;
}

vec2D compute_leadership(boid *boid1, boid_list *neighbours) {
    if (neighbours->count == 0)
        return (vec2D){0, 0};

    boid *leader = neighbours->list[0];

    for (int i = 1; i < neighbours->count; i++)
        if (neighbours->list[i]->strength > leader->strength)
            leader = neighbours->list[i];

    vec2D force = {leader->pos.x - boid1->pos.x, leader->pos.y - boid1->pos.y};
    mul_vec(&force, leader->strength);

    return force;
}

void limit_vel(boid *boid1, double max_vel) {
    double vel = norm(&boid1->vel);

    if (vel > max_vel)
        mul_vec(&boid1->vel, max_vel/vel);
}

void limit_pos(boid *boid1, int limit) {
    if (boid1->pos.x < limit && boid1->acc.x < 0 || boid1->pos.x > WIDTH-limit && boid1->acc.x > 0)
        boid1->acc.x *= -1;

    if (boid1->pos.y < limit && boid1->acc.y < 0 || boid1->pos.y > HEIGHT-limit && boid1->acc.y > 0)
        boid1->acc.y *= -1;
}

void update_boid(boid *boid1, boid_list *boids) {
    boid_list close = get_neighbours(boids, boid1, 20);
    boid_list around = get_neighbours(boids, boid1, 100);

    vec2D separation = compute_separation(boid1, &close);
    vec2D cohesion = compute_cohesion(boid1, &around);
    vec2D alignment = compute_alignment(&around);
    vec2D leadership = compute_leadership(boid1, &around);

    mul_vec(&separation, 0.2);
    mul_vec(&cohesion, 0.5);
    mul_vec(&alignment, 5);
    mul_vec(&leadership, 1);

    add_vec(&boid1->acc, &separation);
    add_vec(&boid1->acc, &cohesion);
    add_vec(&boid1->acc, &alignment);
    add_vec(&boid1->acc, &leadership);

    add_vec(&boid1->vel, &boid1->acc);

    limit_vel(boid1, 2);
    limit_pos(boid1, 20);

    add_vec(&boid1->pos, &boid1->vel);
}