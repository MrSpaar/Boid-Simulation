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
    double vel = norm(&boid->vel);
    if (vel > 2) {
        mul_vec(&boid->vel, 2/vel);
    }

    if (boid->pos.x < 20 && boid->acc.x < 0 || boid->pos.x > WIDTH - 20 && boid->acc.x > 0) {
        boid->acc.x = -boid->acc.x;
    }

    if (boid->pos.y < 20 && boid->acc.y < 0 || boid->pos.y > HEIGHT - 20 && boid->acc.y > 0) {
        boid->acc.y = -boid->acc.y;
    }

    add_vec(&boid->pos, &boid->vel);

    free(close->list);
    free(around->list);

    free(close);
    free(around);

    return 0;
}

void renderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid_t *b) {
    rect->x = (int) b->pos.x;
    rect->y = (int) b->pos.y;
    double angle = atan(b->vel.y/b->vel.x) + M_PI_2;

    if (b->vel.x < 0 && b->vel.y > 0)      angle += M_PI;
    else if (b->vel.x < 0 && b->vel.y < 0) angle -= M_PI;

    angle *= TO_DEG;
    SDL_RenderCopyEx(renderer, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE);
}
