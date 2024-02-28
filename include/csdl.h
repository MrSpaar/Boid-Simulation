#ifndef __BOIDS_CSDL_H
#define __BOIDS_CSDL_H

#include <SDL2/SDL.h>
#include "boids.h"

#define TICK_INTERVAL 16
#define TO_DEG 57.2957795131

#define SDL_OUT(format) SDL_Log(format, SDL_GetError()); rc = 1; goto end
#define ERROR_OUT(format) printf(format); rc = 1; goto end

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} CSDL;

uint32_t CSDL_TicksLeft(uint32_t next_time);
void CSDL_RenderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid_t *b);
void CSDL_Clear(SDL_Renderer *renderer);

#endif // __BOIDS_CSDL_H
