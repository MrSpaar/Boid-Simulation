#include "../include/csdl.h"

int main() {
    CSDL csdl = CSDL_Init(WIDTH, HEIGHT);

    SDL_Rect rect = {.w=12, .h=17};
    SDL_Texture *texture = CSDL_CreateTexture(csdl.renderer, "../boid.bmp");

    SDL_Event event;
    boid_list boids = create_boid_list(300);

    while (1) {
        while(SDL_PollEvent(&event) != 0)
            if(event.type == SDL_QUIT)
                CSDL_Quit(&csdl);

        CSDL_Clear(csdl.renderer);

        for (int i=0; i<boids.count; i++) {
            update_boid(boids.list[i], &boids);
            CSDL_RenderBoid(csdl.renderer, texture, &rect, boids.list[i]);
        }

        SDL_RenderPresent(csdl.renderer);
        SDL_Delay(10);
    }
}
