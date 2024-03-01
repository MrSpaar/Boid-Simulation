#ifndef __BOIDS_CSDL_H
#define __BOIDS_CSDL_H

#include <SDL.h>
#include "boids.hpp"

#define TICK_INTERVAL 16
#define TO_DEG 57.2957795131

class Window {
public:
    explicit Window(const char *path);
    void update();
    ~Window();
private:
    void renderBoid(const Boid &boid);
private:
    std::vector<Boid> boids;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Texture* texture;
    SDL_Renderer *renderer;

    SDL_Rect rect{ .w=9, .h=12 };
};

#endif // __BOIDS_CSDL_H
