#ifndef __BOIDS_BOIDS_H
#define __BOIDS_BOIDS_H

#include <SDL2/SDL.h>
#include "vectors.h"

#define WIDTH 1024
#define HEIGHT 720
#define BOID_COUNT 300

#define TICK_INTERVAL 16
#define TO_DEG 57.2957795131

typedef struct {
    vec2D pos;
    vec2D vel;
    vec2D acc;
} boid_t;

typedef struct {
    boid_t *list;
    int count;
} boid_list_t;

int update_boid(boid_t *boid, boid_list_t *boids);
void renderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid_t *b);

#endif // __BOIDS_BOIDS_H
