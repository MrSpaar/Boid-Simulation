#include "../includes/boids.hpp"

// Mettre à jour un boid en fonction de ses voisins
void Boid::update(const std::vector<Boid> &boids) {
    int count;
    Vec2D separation, cohesion, alignment;

    // Calcul des trois formules, au lieu de créer une liste de voisins et d'avoir
    // trois calculs indépendant, on ne scanne la liste qu'une seule fois pour les trois

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

    // On limite la vélocité si elle est trop grande
    double norm = vel.norm();
    if (norm > 2) {
        vel *= 2/norm;
    }

    pos += vel;

    // Le boid doit faire demi-tour s'il a dépassé la bordure de la fenêtre
    if (pos.x < POS_LIMIT && acc.x < 0 || pos.x > WIDTH-POS_LIMIT && acc.x > 0) {
        acc.x = -DAMPING_FACTOR*acc.x;
    }
    if (pos.y < POS_LIMIT && acc.y < 0 || pos.y > HEIGHT-POS_LIMIT && acc.y > 0) {
        acc.y = -DAMPING_FACTOR*acc.y;
    }
}
