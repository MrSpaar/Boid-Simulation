#ifndef __BOIDS_BOIDS_H
#define __BOIDS_BOIDS_H

#include <cmath>
#include <vector>

#define WIDTH      1024
#define HEIGHT     720
#define BOID_COUNT 300

#define SEPARATION_FACTOR 0.2
#define COHESION_FACTOR   0.5
#define ALIGNMENT_FACTOR  5
#define DAMPING_FACTOR    0.3

#define HIGHER_LIMIT 100
#define LOWER_LIMIT  20
#define POS_LIMIT    20

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

struct Boid;
typedef std::vector<std::reference_wrapper<Boid>> BoidVector;

struct Boid {
    int r, g, b;
    Vec2D pos, vel, acc;

    explicit Boid():
        pos(rand()%(WIDTH-100), rand()%(HEIGHT)),
        acc(-1 + rand()%2, -1 + rand()%2),
        r(rand()%255), g(rand()%255), b(rand()%255) {}

    void update(const std::vector<Boid> &boids);
};


#endif // __BOIDS_BOIDS_H
