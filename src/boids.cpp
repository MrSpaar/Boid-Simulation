#include "../includes/boids.hpp"

void Boid::update(const std::vector<Boid> &boids) {
    int count;
    Vec2D separation, cohesion, alignment;

    // For now, we scan the entire boid list once to detect close and surrounding neighbors
    // No neighbor list is created to avoid unnecessary memory allocation

    for (const Boid &other: boids) {
        double distance = pos.dist(other.pos);
        if (distance == 0) continue;

        if (distance < HIGHER_LIMIT) {
            count++;
            cohesion += other.pos;
            alignment += other.vel;
        }

        if (distance < LOWER_LIMIT) {
            separation += pos.diff(other.pos);
        }
    }

    if (separation.x != 0 || separation.y != 0) {
        acc += separation * SEPARATION_FACTOR;
    }

    if (count != 0) {
        acc += (cohesion/count - pos) * COHESION_FACTOR;
        acc += (alignment/count) * ALIGNMENT_FACTOR;
    }

    vel += acc;

    // Cap the velocity if it exceeds the limit
    double norm = vel.norm();
    if (norm > VEL_LIMIT) {
        vel *= VEL_LIMIT/norm;
    }

    pos += vel;

    // Bounce off the border if the boid gets to close
    if (pos.x < POS_LIMIT && acc.x < 0 || pos.x > WINDOW_WIDTH-POS_LIMIT && acc.x > 0) {
        acc.x = -DAMPING_FACTOR*acc.x;
    }
    if (pos.y < POS_LIMIT && acc.y < 0 || pos.y > WINDOW_HEIGHT-POS_LIMIT && acc.y > 0) {
        acc.y = -DAMPING_FACTOR*acc.y;
    }
}
