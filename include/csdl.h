#ifndef BOIDS_CSDL_H
#define BOIDS_CSDL_H

#include <stdio.h>

#include "boids.h"
#include "vectors.h"
#include "SDL2/SDL.h"

#define TO_DEG 57.2957795131

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} CSDL;


void CSDL_ErrorOut(char *message) {
    SDL_Log(message, SDL_GetError());
    exit(EXIT_FAILURE);
}

CSDL CSDL_Init(int width, int height) {
    CSDL csdl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        CSDL_ErrorOut("Init error : %s\n");

    if (SDL_CreateWindowAndRenderer(width, height, 0, &csdl.window, &csdl.renderer) != 0)
        CSDL_ErrorOut("Window and renderer creation error: %s\n");

    return csdl;
}

SDL_Texture *CSDL_CreateTexture(SDL_Renderer *renderer, char *path) {
    SDL_Surface *surface = NULL;
    surface = SDL_LoadBMP(path);

    if (surface == NULL)
        CSDL_ErrorOut("Surface load error : %s\n");

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL)
        CSDL_ErrorOut("Texture creation error : %s\n");

    return texture;
}

void CSDL_RenderBoid(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, boid_t *b) {
    rect->x = (int) b->pos.x;
    rect->y = (int) b->pos.y;

    double angle = atan(b->vel.y/b->vel.x) + M_PI_2;
    if (b->vel.x < 0 && b->vel.y > 0)
        angle += M_PI;
    else if (b->vel.x < 0 && b->vel.y < 0)
        angle -= M_PI;

    angle *= TO_DEG;

    SDL_RenderCopyEx(renderer, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE);
}

void CSDL_Clear(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 186, 166, 116, 0);
}

void CSDL_Quit(CSDL *csdl, boid_list_t *boids) {
    SDL_DestroyRenderer(csdl->renderer);
    SDL_DestroyWindow(csdl->window);
    free(boids->list);
    SDL_Quit();
}

#endif
