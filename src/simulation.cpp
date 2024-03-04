#include <ctime>
#include <iostream>
#include <stdexcept>

#include "../includes/simulation.hpp"


Simulation::Simulation(const char *boidTexturePath) {
    // Use Wayland if supported (avoids GTK errors)
    if (getenv("WAYLAND_DISPLAY")) {
        putenv((char*) "GDK_BACKEND=wayland");
    }

    // Initialize the library with window and events
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    // The texture is created from a bitmap file
    if ((surface = SDL_LoadBMP(boidTexturePath)) == NULL) {
        throw std::runtime_error(SDL_GetError());
    }

    if ((texture = SDL_CreateTextureFromSurface(renderer, surface)) == NULL) {
        throw std::runtime_error(SDL_GetError());
    }

    // To avoid generating the same numbers, the current time is used as a see
    srand(time(NULL));

    // Fill the vector with random boids
    boids.reserve(BOID_COUNT);
    for (int i = 0; i < BOID_COUNT; i++) {
        boids.push_back({
            (char) (rand()%3),
            { (double) (rand()%WINDOW_WIDTH), (double) (rand()%WINDOW_HEIGHT) },
            { (double) (-1 + rand()%2), (double) (-1 + rand()%2) },
            { (double) (-1 + rand()%2), (double) (-1 + rand()%2) }
        });
    }
}

void Simulation::renderBoid(const Boid &boid) {
    rect.x = (int) boid.pos.x;
    rect.y = (int) boid.pos.y;

    // The boid's angle is computed from it's velocity
    double angle = atan(boid.vel.y / boid.vel.x) + M_PI_2;
    if (boid.vel.x < 0 && boid.vel.y > 0)
        angle += M_PI;
    else if (boid.vel.x < 0 && boid.vel.y < 0)
        angle -= M_PI;

    // Set the color and render the boid
    const SDL_Color& color = teams[boid.team];
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

    SDL_RenderCopyEx(
        renderer, texture, NULL, &rect,
        angle*57.2957795131, NULL, SDL_FLIP_NONE
    );
}

void Simulation::update() {
    SDL_RenderClear(renderer);
    uint32_t now, nextTicks = SDL_GetTicks() + TICK_INTERVAL;

    for (int i = 0; i < boids.size(); i++) {
        Boid& boid = boids.at(i);

        boid.update(boids);
        renderBoid(boid);
    }

    SDL_RenderPresent(renderer);

    // TICK_INTERVAL=16ms at 60 FPS but render time can be less than 16ms
    // so the time delta is computed to cap the framerate at 60 FPS

    now = SDL_GetTicks();
    if (now < nextTicks) {
        SDL_Delay(nextTicks - now);
    } else {
        std::cout << "Frame took too long to render" << std::endl;
    }
}

// Custom destructor so that the program ends gracefully
Simulation::~Simulation() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
