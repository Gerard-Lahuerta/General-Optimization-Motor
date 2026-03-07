
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
int vector_free(Vector *v);


// OTHER UTILITY FUNCTIONS
int vector_fill_random(Vector *v, double min, double max);
int vector_resize(Vector *v, unsigned int new_size);
int set_vector_components(Vector *v, double *components, unsigned int size);


// AUXILARY FUNCTIONS
int vector_print(const Vector *v);


// Vector dimension comparation function
static inline int same_size(const Vector *a, const Vector *b) {
    return a->size == b->size;
}

// INLINE FUNCTIONS (BASIC UTILITIES) - WITH CHECKERS
static inline int vector_copy(Vector *dst, const Vector *src) {
    ASSERT_ERROR(
        !dst || !src || !dst->components || !src->components,
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(dst, src), VEC_ERR_DIM);
    ASSERT_ERROR(dst->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < src->size; i++)
        dst->components[i] = src->components[i];
    return 0;
}

static inline int vector_fill(Vector *v, double value) {
    ASSERT_ERROR(!v || !v->components, VEC_ERR_NULL);
    ASSERT_ERROR(v->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < v->size; i++) v->components[i] = value;
    return 0;
}

static inline int vector_zero(Vector *v) {
    ASSERT_ERROR(!v || !v->components, VEC_ERR_NULL);
    ASSERT_ERROR(v->size == 0, VEC_ERR_DIM_0);

    memset(v->components, 0, v->size * sizeof(double));
    return 0;
}


// INLINE FUNCTIONS (BASIC UTILITIES) - WITHOUT CHECKERS / RAW VERSION
static inline void vector_copy_raw(
    Vector *restrict dst,
    const Vector *restrict src
) {
    for (unsigned i = 0; i < src->size; i++)
        dst->components[i] = src->components[i];
}

static inline void vector_fill_raw(Vector *v, double value) {
    for (unsigned i = 0; i < v->size; i++)
        v->components[i] = value;
}


// INLINE FUNCTIONS (BASIC OPERATIONS) - WITH CHECKERS
static inline int vector_add(
    Vector *restrict res,
    const Vector *restrict a,
    const Vector *restrict b
) {
    ASSERT_ERROR(
        (!a || !b || !res
         || !a->components || !b->components || !res->components),
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(a, b) || !same_size(a, res), VEC_ERR_DIM);
    ASSERT_ERROR(a->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] + b->components[i];
    return 0;
}

static inline int vector_sub(
    Vector *restrict res,
    const Vector *restrict a,
    const Vector *restrict b
) {
    ASSERT_ERROR(
        (!a || !b || !res
         || !a->components || !b->components || !res->components),
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(a, b) || !same_size(a, res), VEC_ERR_DIM);
    ASSERT_ERROR(a->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] - b->components[i];
    return 0;
}

static inline int vector_scale(Vector *res, const Vector *v, double alpha) {
    ASSERT_ERROR(
        !v || !res || !v->components || !res->components,
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(v, res), VEC_ERR_DIM);
    ASSERT_ERROR(v->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < v->size; i++)
        res->components[i] = alpha * v->components[i];
    return 0;
}

static inline int vector_axpy(
    Vector *restrict res,
    double alpha,
    const Vector *restrict x,
    const Vector *restrict y
) {
    ASSERT_ERROR(
        (!x || !y || !res
         || !x->components || !y->components || !res->components),
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(x, y) || !same_size(x, res), VEC_ERR_DIM);
    ASSERT_ERROR(x->size == 0, VEC_ERR_DIM_0);

    for (unsigned i = 0; i < x->size; i++)
        res->components[i] = alpha * x->components[i] + y->components[i];
    return 0;
}

static inline double vector_dot(const Vector *a, const Vector *b) {
    ASSERT_ERROR(
        !a || !b || !a->components || !b->components,
        VEC_ERR_NULL
    );
    ASSERT_ERROR(!same_size(a, b), VEC_ERR_DIM);
    ASSERT_ERROR(a->size == 0, VEC_ERR_DIM_0);

    double sum = 0.0;
    for (unsigned i = 0; i < a->size; i++)
        sum += a->components[i] * b->components[i];
    return sum;
}

static inline double vector_norm2_sq(const Vector *v) {
    ASSERT_ERROR(!v || !v->components, VEC_ERR_NULL);
    ASSERT_ERROR(v->size == 0, VEC_ERR_DIM_0);

    double sum = 0.0;
    for (unsigned i = 0; i < v->size; i++)
        sum += v->components[i] * v->components[i];
    return sum;
}


// INLINE FUNCTIONS (BASIC OPERATIONS) - WITHOUT CHECKERS / RAW VERSION
static inline void vector_add_raw(
    Vector *restrict res,
    const Vector *restrict a,
    const Vector *restrict b
) {
    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] + b->components[i];
}

static inline void vector_sub_raw(
    Vector *restrict res,
    const Vector *restrict a,
    const Vector *restrict b
) {
    for (unsigned i = 0; i < a->size; i++)
        res->components[i] = a->components[i] - b->components[i];
}

static inline void vector_scale_raw(
    Vector *restrict res,
    const Vector *restrict v,
    double alpha
) {
    for (unsigned i = 0; i < v->size; i++)
        res->components[i] = alpha * v->components[i];
}

static inline void vector_axpy_raw(
    Vector *restrict res,
    double alpha,
    const Vector *restrict x,
    const Vector *restrict y
) {
    for (unsigned i = 0; i < x->size; i++)
        res->components[i] = alpha * x->components[i] + y->components[i];
}

static inline double vector_dot_raw(const Vector *a, const Vector *b) {
    double sum = 0.0;
    for (unsigned i = 0; i < a->size; i++)
        sum += a->components[i] * b->components[i];
    return sum;
}

static inline double vector_norm2_sq_raw(const Vector *v){
    double sum = 0.0;
    for (unsigned i = 0; i < v->size; i++)
        sum += v->components[i] * v->components[i];
    return sum;
}

// INLINE FUNCTIONS (OTHER UTILITIES)
static inline double vector_max_abs(const Vector *v) {
    if (!v || v->size == 0)
        return -1.0;
    double max_v = 0.0;
    for (unsigned i = 0; i < v->size; i++) {
        double abs_v = fabs(v->components[i]);
        if (abs_v > max_v) max_v = abs_v;
    }
    return max_v;
}

static inline double vector_max_abs_raw(const Vector *v) {
    double abs_v, max_v = 0.0;
    for (unsigned i = 0; i < v->size; i++) {
        abs_v = fabs(v->components[i]);
        if (abs_v > max_v) max_v = abs_v;
    }
    return max_v;
}

#endif