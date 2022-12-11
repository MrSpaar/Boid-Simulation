#ifndef BOIDS_CSDL_H
#define BOIDS_CSDL_H

#include <stdio.h>
#include "SDL2/SDL.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} CSDL;

CSDL CSDL_Init(int width, int height);
void CSDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
void CSDL_Quit(SDL_Window *window, SDL_Renderer *renderer);
void CSDL_ErrorOut(char *message);

#endif
