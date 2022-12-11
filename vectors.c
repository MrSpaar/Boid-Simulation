#include "vectors.h"

void add_vec(vec2D *vec1, vec2D *vec2) {
    vec1->x += vec2->x;
    vec1->y += vec2->y;
}

vec2D sub_vec(vec2D *vec1, vec2D *vec2) {
    vec2D result = {vec1->x - vec2->x, vec1->y - vec2->y};
    return result;
}

void mul_vec(vec2D *vec, double scalar) {
    vec->x *= scalar;
    vec->y *= scalar;
}

void div_vec(vec2D *vec, double scalar) {
    vec->x /= scalar;
    vec->y /= scalar;
}

double dist(vec2D *vec1, vec2D *vec2) {
    return sqrt(pow(vec1->x - vec2->x, 2) + pow(vec1->y - vec2->y, 2));
}

double norm(vec2D *vec) {
    return sqrt(pow(vec->x, 2) + pow(vec->y, 2));
}
