#ifndef BOIDS_VECTORS_H
#define BOIDS_VECTORS_H

#include <math.h>


typedef struct {
    double x;
    double y;
} vec2D;


inline void add_vec(vec2D *vec1, vec2D *vec2) {
    vec1->x += vec2->x;
    vec1->y += vec2->y;
}

inline void sub_vec(vec2D *vec1, vec2D *vec2) {
    vec1->x -= vec2->x;
    vec1->y -= vec2->y;
}

inline vec2D static_sub_vec(vec2D *vec1, vec2D *vec2) {
    return (vec2D) {
            vec1->x - vec2->x,
            vec1->y - vec2->y
    };
};

inline void mul_vec(vec2D *vec, double scalar) {
    vec->x *= scalar;
    vec->y *= scalar;
}

inline void div_vec(vec2D *vec, double scalar) {
    vec->x /= scalar;
    vec->y /= scalar;
}

inline double dist(vec2D *vec1, vec2D *vec2) {
    return sqrt(pow(vec1->x - vec2->x, 2) + pow(vec1->y - vec2->y, 2));
}

inline double norm(vec2D *vec) {
    return sqrt(pow(vec->x, 2) + pow(vec->y, 2));
}

#endif
