#include "csdl.h"
#include "boids.h"

int main() {
    CSDL csdl = CSDL_Init(1024, 720);

    SDL_Event event;
    boid_list boids = create_boid_list(100);

    while (1) {
        while(SDL_PollEvent(&event) != 0)
            if(event.type == SDL_QUIT)
                CSDL_Quit(&csdl);

        SDL_SetRenderDrawColor(csdl.renderer, 0, 0, 0, 0);
        SDL_RenderClear(csdl.renderer);
        SDL_SetRenderDrawColor(csdl.renderer, 186, 166, 116, 0);

        for (int i=0; i<boids.count; i++) {
            update_boid(boids.list[i], &boids);
            CSDL_RenderFillCircle(csdl.renderer, boids.list[i]->pos.x, boids.list[i]->pos.y, 2);
        }

        SDL_RenderPresent(csdl.renderer);
        SDL_Delay(10);
    }
}
