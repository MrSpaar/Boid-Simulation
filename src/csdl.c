#include "csdl.h"

CSDL CSDL_Init(int width, int height) {
    CSDL csdl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        CSDL_ErrorOut("Init error : %s\n");

    if (SDL_CreateWindowAndRenderer(width, height, 0, &csdl.window, &csdl.renderer) != 0)
        CSDL_ErrorOut("Window and renderer creation error: %s\n");

    return csdl;
}

void CSDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    int offsetx=0, offsety=radius, d=radius-1;

    while (offsety >= offsetx) {
        SDL_RenderDrawLine(renderer, x-offsety, y+offsetx,
                           x+offsety, y+offsetx);
        SDL_RenderDrawLine(renderer, x-offsetx, y+offsety,
                           x+offsetx, y+offsety);
        SDL_RenderDrawLine(renderer, x-offsetx, y-offsety,
                           x+offsetx, y-offsety);
        SDL_RenderDrawLine(renderer, x-offsety, y-offsetx,
                           x+offsety, y-offsetx);

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx += 1;
        } else if (d < 2*(radius-offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2*(offsety-offsetx-1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void CSDL_Quit(CSDL *csdl) {
    SDL_DestroyWindow(csdl->window);
    SDL_DestroyRenderer(csdl->renderer);
    SDL_Quit();

    exit(EXIT_SUCCESS);
}

void CSDL_ErrorOut(char *message) {
    SDL_Log(message, SDL_GetError());
    exit(EXIT_FAILURE);
}
