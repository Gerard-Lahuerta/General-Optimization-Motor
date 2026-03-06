
/*
**
**
**
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <string.h>
#include <math.h>

#include "logger.h"
#include "error.h"


typedef struct
{
    unsigned int size;
    double *components;
} Vector;


// VECTOR CREATION
int  vector_init(Vector *v, unsigned int size);
void vector_free(Vector *v);


// OTHER UTILITY FUNCTIONS
void vector_fill_random(Vector *v, double min, double max);
int vector_resize(Vector *v, unsigned int new_size);
int set_vector_components(Vector *v, double *components, unsigned int size);


// AUXILARY FUNCTIONS
void vector_print(const Vector *v);


// INLINE FUNCTIONS (BASIC UTILITIES) - WITH CHECKERS
static inline int vector_copy(Vector *dst, const Vector *src) {
    if (!dst || !src || !dst->components || !src->components){
        LOG_ERROR("vector_copy: NULL pointer.");
        return- 1;
    }
    if (dst->size != src->size) {
        LOG_ERROR("vector_copy: Incompatible sizes (dst: %u, src: %u).",
                  dst->size, src->size);
        return 1;
    }
    for (unsigned i = 0; i < src->size; i++)
        dst->components[i] = src->components[i];
    return 0;
}

static inline int vector_fill(Vector *v, double value) {
    if (!v || !v->components){
        LOG_ERROR("vector_copy: NULL pointer.");
        return -1;
    }
    if (v->size == 0){
        LOG_ERROR("vector_fill: Operation on vectors of size 0.");
        return 2;
    }
    for (unsigned i = 0; i < v->size; i++) v->components[i] = value;
    return 0;
}

static inline int vector_zero(Vector *v) {
    if (!v || !v->components) {
        LOG_ERROR("vector_zero: NULL pointer.");
        return -1;
    }
    if (v->size == 0){
        LOG_ERROR("vector_zero: Incompatible sizes (v: %d)", v->size);
        return 2;
    }

    memset(v->components, 0, v->size * sizeof(double));
    return 0;
}


// INLINE FUNCTIONS (BASIC UTILITIES) - WITHOUT CHECKERS / RAW VERSION
static inline void vector_copy_raw(Vector *restrict dst, const Vector *restrict src) {
    for (unsigned i = 0; i < src->size; i++)
        dst->components[i] = src->components[i];
}

static inline void vector_fill_raw(Vector *v, double value) {
    for (unsigned i = 0; i < v->size; i++)
        v->components[i] = value;
}


// INLINE FUNCTIONS (BASIC OPERATIONS) - WITH CHECKERS
static inline int same_size(const Vector *a, const Vector *b) {
    return a->size == b->size;
}

static inline int vector_add(Vector *restrict res, const Vector *restrict a, const Vector *restrict b) {
    if (!same_size(a, b) || !same_size(a, res)) {
        LOG_ERROR("vector_add: Incompatible sizes (res: %u, a: %u, b: %u).",
                  res->size, a->size, b->size);
        return 1;
    }
    if (a->size == 0) {
        LOG_ERROR("vector_add: Operation on vectors of size 0.");
        return 2;
    }

    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] + b->components[i];
    return 0;
}

static inline int vector_sub(Vector *restrict res, const Vector *restrict a, const Vector *restrict b) {
    if (!same_size(a, b) || !same_size(a, res)) {
        LOG_ERROR("vector_sub: Incompatible sizes (res: %u, a: %u, b: %u).",
                  res->size, a->size, b->size);
        return 1;
    }
    if (a->size == 0) {
        LOG_ERROR("vector_sub: Operation on vectors of size 0.");
        return 2;
    }

    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] - b->components[i];
    return 0;
}

static inline int vector_scale(Vector *res, const Vector *v, double alpha) {
    if (!same_size(res, v)) {
        LOG_ERROR("vector_scale: Incompatible sizes (res: %u, v: %u).",
                  res->size, v->size);
        return 1;
    }
    if (v->size == 0) {
        LOG_ERROR("vector_scale: Operation on vector of size 0.");
        return 2;
    }

    for (unsigned i = 0; i < v->size; i++)
        res->components[i] = alpha * v->components[i];
    return 0;
}

static inline int vector_axpy(Vector *restrict res, double alpha, const Vector *restrict x, const Vector *restrict y) {
    if (!same_size(x, y) || !same_size(x, res)) {
        LOG_ERROR("vector_axpy: Incompatible sizes (res: %u, x: %u, y: %u).",
                  res->size, x->size, y->size);
        return 1;
    }
    if (x->size == 0) {
        LOG_ERROR("vector_axpy: Operation on vectors of size 0.");
        return 2;
    }

    for (unsigned i = 0; i < x->size; i++)
        res->components[i] = alpha * x->components[i] + y->components[i];
    return 0;
}

static inline double vector_dot(const Vector *a, const Vector *b) {
    if (!same_size(a, b)) {
        LOG_ERROR("vector_dot: Incompatible sizes (a: %u, b: %u).", a->size, b->size);
        return 0.0;
    }
    if (a->size == 0) return 0.0;

    double sum = 0.0;
    for (unsigned i = 0; i < a->size; i++)
        sum += a->components[i] * b->components[i];
    return sum;
}

static inline double vector_norm2_sq(const Vector *v) {
    if (v->size == 0) return 0.0;

    double sum = 0.0;
    for (unsigned i = 0; i < v->size; i++)
        sum += v->components[i] * v->components[i];
    return sum;
}


// INLINE FUNCTIONS (BASIC OPERATIONS) - WITHOUT CHECKERS / RAW VERSION
static inline void vector_add_raw(Vector *restrict res, const Vector *restrict a, const Vector *restrict b) {
    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] + b->components[i];
}

static inline void vector_sub_raw(Vector *restrict res, const Vector *restrict a, const Vector *restrict b) {
    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] - b->components[i];
}

static inline void vector_scale_raw(Vector *restrict res, const Vector *restrict v, double alpha) {
    for (unsigned i = 0; i < v->size; i++)
        res->components[i] = alpha * v->components[i];
}

static inline void vector_axpy_raw(Vector *restrict res, double alpha, const Vector *restrict x, const Vector *restrict y) {
    for (unsigned i = 0; i < x->size; i++)
        res->components[i] = alpha * x->components[i] + y->components[i];
}

static inline double vector_dot_raw(const Vector *a, const Vector *b) {
    double sum = 0.0;
    for (unsigned i = 0; i < a->size; i++)
        sum += a->components[i] * b->components[i];
    return sum;
}


// INLINE FUNCTIONS (OTHER UTILITIES)
static inline double vector_max_abs(const Vector *v) {
    if (!v || v->size == 0) return 0.0;
    double max_v = 0.0;
    for (unsigned i = 0; i < v->size; i++) {
        double abs_v = fabs(v->components[i]);
        if (abs_v > max_v) max_v = abs_v;
    }
    return max_v;
}

#endif