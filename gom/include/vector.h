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

// VECTOR CREATION
int  vector_init(Vector *v, unsigned int size);
void vector_free(Vector *v);

// BASIC UTILITIES
int vector_zero(Vector *v);
int vector_fill(Vector *v, double value);
int vector_copy(Vector *dst, const Vector *src);

// BASIC OPERATIONS
int vector_add(Vector *res, const Vector *a, const Vector *b);
int vector_sub(Vector *res, const Vector *a, const Vector *b);
int vector_scale(Vector *res, const Vector *v, double alpha);
double vector_dot(const Vector *a, const Vector *b);
double vector_norm2(const Vector *v);

// OTHER UTILITY FUNCTIONS
int vector_axpy(Vector *res, double alpha, const Vector *x, const Vector *y);
double vector_max_abs(const Vector *v);
void vector_fill_random(Vector *v, double min, double max);
int vector_resize(Vector *v, unsigned int new_size);
int set_vector_components(Vector *v, double *components, unsigned int size);

// AUXILARY FUNCTIONS
void vector_print(const Vector *v);

#endif