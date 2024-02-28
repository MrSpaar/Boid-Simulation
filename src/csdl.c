#include "../include/csdl.h"

uint32_t CSDL_TicksLeft(uint32_t next_time) {
    uint32_t now = SDL_GetTicks();
    if (next_time < now)
        return 0;
    return next_time - now;
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
