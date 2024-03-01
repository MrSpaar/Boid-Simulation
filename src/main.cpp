#include "../includes/window.hpp"

int main() {
    Window window("../images/boid.bmp");

    SDL_Event event;
    bool paused = false;

    while (1) {
        while(SDL_PollEvent(&event) != 0) {
            // On quitte si l'utilisateur a fermé la fenêtre
            if(event.type == SDL_QUIT) {
                return 0;
            }

            // On inverse l'état de pause si l'utilisateur appuie sur espace
            if (event.key.keysym.sym == SDLK_SPACE) {
                paused = !paused;
            }
        }

        if (paused) {
            continue;
        }

        // On met à jour la simulation
        window.update();
    }

    return 0;
}
