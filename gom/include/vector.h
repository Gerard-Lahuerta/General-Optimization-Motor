#ifndef UNROLL_FACTOR
#define UNROLL_FACTOR 8
#endif

#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    unsigned int size;
    double *components;
} Vector;

Vector create_vector(unsigned size);

void vector_zero(Vector *v);

void vector_resize(Vector *v, unsigned int new_size);
void free_vector(Vector *v);

void assign_vector_components(Vector *v, double *components, unsigned int size);

void sum_vectors(Vector *res, Vector *v, Vector *u);

#endif