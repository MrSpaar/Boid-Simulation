#pragma once

#include <vector>
#include "vec2D.hpp"
#include "params.hpp"


struct Boid {
    int r, g, b;
    Vec2D pos, vel, acc;

    explicit Boid():
        pos(rand()%WINDOW_WIDTH, rand()%WINDOW_HEIGHT),
        vel(-1 + rand()%2, -1 + rand()%2),
        acc(-1 + rand()%2, -1 + rand()%2),
        r(rand()%255), g(rand()%255), b(rand()%255) {}

    void update(const std::vector<Boid> &boids);
};
