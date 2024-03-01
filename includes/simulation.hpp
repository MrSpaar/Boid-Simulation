#pragma once

#include <SDL.h>
#include "boids.hpp"


class Simulation {
public:
    explicit Simulation(const char *boidTexturePath);
    void update();
    ~Simulation();
private:
    void renderBoid(const Boid &boid);
private:
    std::vector<Boid> boids;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Texture* texture;
    SDL_Renderer *renderer;
    SDL_Rect rect{ .w=BOID_WIDTH, .h=BOID_HEIGHT };
};
