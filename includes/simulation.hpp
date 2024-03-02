#pragma once

#include <SDL.h>
#include "boids.hpp"
#include "params.hpp"


class Simulation {
public:
    explicit Simulation(const char *boidTexturePath);
    void update();
    ~Simulation();
private:
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Texture* texture;
    SDL_Renderer *renderer;
    SDL_Rect rect{ .w=BOID_WIDTH, .h=BOID_HEIGHT };

    std::vector<Boid> boids;
    void renderBoid(const Boid &boid);
};
