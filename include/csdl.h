#ifndef __BOIDS_CSDL_H
#define __BOIDS_CSDL_H

#include <SDL2/SDL.h>
#include "boids.h"

#define TO_DEG 57.2957795131
#define TICK_INTERVAL 16


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} CSDL;


void CSDL_ErrorOut(char *message);
CSDL CSDL_Init(int width, int height);

uint32_t CSDL_TicksLeft(uint32_t next_time);
SDL_Texture *CSDL_CreateTexture(SDL_Renderer *renderer, char *path);

void CSDL_RenderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid_t *b);

void CSDL_Clear(SDL_Renderer *renderer);
void CSDL_Quit(CSDL *csdl, boid_list_t *boids);

#endif // __BOIDS_CSDL_H
