#ifndef BOIDS_CSDL_H
#define BOIDS_CSDL_H

#include <stdio.h>

#include "boids.h"
#include "vectors.h"
#include "SDL2/SDL.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} CSDL;

CSDL CSDL_Init(int width, int height);
SDL_Texture *CSDL_CreateTexture(SDL_Renderer *renderer, char *path);
void CSDL_RenderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid *b);
void CSDL_Clear(SDL_Renderer *renderer);
void CSDL_Quit(CSDL *csdl);
void CSDL_ErrorOut(char *message);

#endif
