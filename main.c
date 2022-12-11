#include "csdl.h"

int main() {
    CSDL csdl = CSDL_Init(1024, 720);

    SDL_Event event;
    int count = 20;

    while (1) {
        while(SDL_PollEvent(&event) != 0)
            if(event.type == SDL_QUIT)
                CSDL_Quit(csdl.window, csdl.renderer);

        SDL_SetRenderDrawColor(csdl.renderer, 0, 0, 0, 0);
        SDL_RenderClear(csdl.renderer);
        SDL_SetRenderDrawColor(csdl.renderer, 186, 166, 116, 0);

        count++;
        CSDL_RenderFillCircle(csdl.renderer, count, count, 20);

        SDL_RenderPresent(csdl.renderer);
        SDL_Delay(2);
    }
}
