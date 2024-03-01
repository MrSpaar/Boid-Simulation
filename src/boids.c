#include <stdlib.h>
#include "../include/boids.h"

int update_boid(boid_t *boid, boid_list_t *boids) {
    int count = 0;
    vec2D separation = { 0, 0 }, cohesion = { 0, 0 }, alignment = { 0, 0 };
    
    for (int i = 0; i < boids->count; i++) {
        double distance = dist(&boid->pos, &boids->list[i].pos);
        if (distance == 0) continue;

        if (distance < HIGHER_LIMIT) {
            count++;
            add_vec(&cohesion, &boids->list[i].pos);
            add_vec(&alignment, &boids->list[i].vel);
        }

        if (distance < LOWER_LIMIT) {
            vec2D diff = static_sub_vec(&boid->pos, &boids->list[i].pos);
            add_vec(&separation, &diff);
        }
    }

    if (separation.x != 0 || separation.y != 0) {
        mul_vec(&separation, SEPARATION_FACTOR);
        add_vec(&boid->acc, &separation);
    }

    if (count != 0) {
        div_vec(&cohesion, count);
        sub_vec(&cohesion, &boid->pos);

        mul_vec(&cohesion, COHESION_FACTOR);
        mul_vec(&alignment, ALIGNMENT_FACTOR/count);

        add_vec(&boid->acc, &cohesion);
        add_vec(&boid->acc, &alignment);
    }

    add_vec(&boid->vel, &boid->acc);
    double vel = norm(&boid->vel);
    if (vel > 2) {
        mul_vec(&boid->vel, 2/vel);
    }

    if (boid->pos.x < BORDER_LIMIT && boid->acc.x < 0 || boid->pos.x > WIDTH-BORDER_LIMIT && boid->acc.x > 0) {
        boid->acc.x = -DAMPING_FACTOR*boid->acc.x;
    }

    if (boid->pos.y < BORDER_LIMIT && boid->acc.y < 0 || boid->pos.y > HEIGHT-BORDER_LIMIT && boid->acc.y > 0) {
        boid->acc.y = -DAMPING_FACTOR*boid->acc.y;
    }

    add_vec(&boid->pos, &boid->vel);
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
