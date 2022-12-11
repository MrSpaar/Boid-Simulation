#ifndef BOIDS_VECTORS_H
#define BOIDS_VECTORS_H

#include <math.h>

typedef struct {
    double x;
    double y;
} vec2D;

void add(vec2D *vec1, vec2D *vec2);
vec2D sub(vec2D *vec1, vec2D *vec2);
void mul(vec2D *vec, double scalar);
void div(vec2D *vec, double scalar);
double dist(vec2D *vec1, vec2D *vec2);

#endif
