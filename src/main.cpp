#include "../includes/simulation.hpp"

int main() {
    Simulation sim("../images/boid.bmp");

    SDL_Event event;
    bool paused = false;

    while (1) {
        while(SDL_PollEvent(&event) != 0) {
            // End the program if the window is closed
            if(event.type == SDL_QUIT) {
                return 0;
            }

            // Pause or unpause the simulation if space is pressed
            if (event.key.keysym.sym == SDLK_SPACE) {
                paused = !paused;
            }
        }

        if (paused) {
            continue;
        }

        // Update the simulation and render the frame
        sim.update();
    }

    return 0;
}
