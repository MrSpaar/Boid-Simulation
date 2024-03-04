#pragma once

#include <cmath>
#include <vector>


struct Vec2D {
    double x = 0, y = 0;

    void operator*=(double scalar) { x *= scalar; y *= scalar; }
    void operator+=(const Vec2D &other) { x += other.x; y += other.y; }
    void operator-=(const Vec2D &other) { x -= other.x; y -= other.y; }

    Vec2D& operator*(double scalar) {
        x *= scalar; y *= scalar;
        return *this;
    }

    Vec2D& operator/(double scalar) {
        x /= scalar; y /= scalar;
        return *this;
    }

    Vec2D& operator-(const Vec2D &other) {
        x -= other.x; y -= other.y;
        return *this;
    }

    Vec2D diff(const Vec2D &other) {
        return { x - other.x, y - other.y };
    }

    double norm() {
        return std::sqrt(x*x + y*y);
    }

    double dist(const Vec2D &other) {
        return std::sqrt(
            std::pow(x - other.x, 2) + std::pow(y - other.y, 2)
        );
    }
};

struct Boid {
    char team;
    Vec2D pos, vel, acc;
    void update(const std::vector<Boid> &boids);
};
