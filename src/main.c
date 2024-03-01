#include <time.h>
#include "../include/boids.h"

#define SDL_OUT(format) SDL_Log(format, SDL_GetError()); rc = 1; goto end
#define ERROR_OUT(format) printf(format); rc = 1; goto end

int main() {
    if (getenv("WAYLAND_DISPLAY")) {
        putenv("GDK_BACKEND=wayland");
    }

    int rc = 0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_OUT("Error while initializing SDL: %s\n");
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0) {
        SDL_OUT("Error while creating window and renderer: %s\n");
    }

    SDL_Surface *surface = SDL_LoadBMP("../images/boid.bmp");
    if (surface == NULL) {
        SDL_OUT("Error while creating surface: %s\n");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        SDL_OUT("Error while creating texture: %s\n");
    }

    boid_list_t boids = { calloc(sizeof(boid_t), BOID_COUNT), BOID_COUNT };
    if (boids.list == NULL) {
        ERROR_OUT("Error while allocating memory for boids\n");
    }

    srand(time(NULL));
    for (int i = 0; i < BOID_COUNT; i++) {
        boids.list[i].pos.x = rand()%WIDTH;
        boids.list[i].pos.y = rand()%HEIGHT;

        boids.list[i].acc.x = -1 + rand()%2;
        boids.list[i].acc.y = -1 + rand()%2;
    }

    SDL_Event event;
    uint32_t next_time, now;
    SDL_Rect rect = { .w=9, .h=12 };

    while (1) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                goto end;
            }
        }

        next_time = SDL_GetTicks() + TICK_INTERVAL;
        SDL_RenderClear(renderer);


        for (int i = 0; i < boids.count; i++) {
            if (update_boid(&boids.list[i], &boids) < 0) {
                ERROR_OUT("Error while allocating memory for neighbors\n");
            }

            renderBoid(renderer, texture, &rect, &boids.list[i]);
        }

        SDL_RenderPresent(renderer);
        now = SDL_GetTicks();

        if (now < next_time) {
            SDL_Delay(next_time - now);
        }
    }

    end:
        if (surface != NULL) SDL_FreeSurface(surface);
        if (texture != NULL) SDL_DestroyTexture(texture);
        if (boids.list != NULL) free(boids.list);

        if (window != NULL) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
        }

        SDL_Quit();
        return rc;
}
