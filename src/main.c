#include <time.h>
#include "../include/csdl.h"

int main() {
    int rc = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_OUT("Error while initializing SDL: %s\n");
    }

    CSDL csdl = { NULL, NULL };
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &csdl.window, &csdl.renderer) != 0) {
        SDL_OUT("Error while creating window and renderer: %s\n");
    }

    SDL_Surface *surface = SDL_LoadBMP("../images/boid.bmp");
    if (surface == NULL) {
        SDL_OUT("Error while creating surface: %s\n");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(csdl.renderer, surface);
    if (texture == NULL) {
        SDL_OUT("Error while creating texture: %s\n");
    }

    boid_list_t boids = { calloc(sizeof(boid_t), BOID_COUNT), BOID_COUNT };
    if (boids.list == NULL) {
        ERROR_OUT("Error while allocating memory for boids\n");
    }

    srand(time(NULL));
    for (int i = 0; i < BOID_COUNT; i++) {
        boids.list[i].pos.x = rand() % WIDTH;
        boids.list[i].pos.y = rand() % HEIGHT;
    }

    SDL_Event event;
    uint32_t next_time;
    SDL_Rect rect = { .w=12, .h=17 };

    while (1) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                goto end;
            }
        }

        next_time = SDL_GetTicks() + TICK_INTERVAL;
        CSDL_Clear(csdl.renderer);

        for (int i = 0; i < boids.count; i++) {
            if (update_boid(&boids.list[i], &boids) < 0) {
                ERROR_OUT("Error while allocating memory for neighbors\n");
            }

            CSDL_RenderBoid(csdl.renderer, texture, &rect, &boids.list[i]);
        }

        SDL_RenderPresent(csdl.renderer);
        SDL_Delay(CSDL_TicksLeft(next_time));
        next_time += TICK_INTERVAL;
    }

    end:
        if (surface != NULL) SDL_FreeSurface(surface);
        if (texture != NULL) SDL_DestroyTexture(texture);
        if (boids.list != NULL) free(boids.list);

        if (csdl.window != NULL) {
            SDL_DestroyRenderer(csdl.renderer);
            SDL_DestroyWindow(csdl.window);
        }

        SDL_Quit();
        return rc;
}
