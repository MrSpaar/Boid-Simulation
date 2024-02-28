#ifndef __BOIDS_VECTORS_H
#define __BOIDS_VECTORS_H

typedef struct {
    double x;
    double y;
} vec2D;

void add_vec(vec2D *vec1, vec2D *vec2);
void sub_vec(vec2D *vec1, vec2D *vec2);
vec2D static_sub_vec(vec2D *vec1, vec2D *vec2);
void mul_vec(vec2D *vec, double scalar);
void div_vec(vec2D *vec, double scalar);
double dist(vec2D *vec1, vec2D *vec2);
double norm(vec2D *vec);

#endif // __BOIDS_VECTORS_H
