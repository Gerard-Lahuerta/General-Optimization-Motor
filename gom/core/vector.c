
/*
**
**
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "logger.h"

/*
** ------------- INTERNAL FUNCTIONS -------------
*/

int same_size(const Vector *a, const Vector *b)
{
    return a->size == b->size;
}


/*
** ------------- VECTOR CREATION -------------
*/

int vector_init(Vector *v, unsigned int size)
{
    v->size = size;
    if (size == 0){
        LOG_WARN("Introduced vector with size 0.");
    }
    else{
        v->components = (double *)calloc(size, sizeof(double));

        if (v->components == NULL)
        {
            v->size = 0;
            LOG_ERROR("Not enough memory, vector size set to 0.");
            return 1;
        }
    }
    return 0;
}

void vector_free(Vector *v)
{
    free(v->components);
}


/*
** ------------- BASIC UTILITIES -------------
*/

int vector_zero(Vector *v)
{
    if (v->size == 0){
        LOG_ERROR("Vector with dimensión 0 introduced.");
        return 1;
    }
    if (v->components == NULL){
        LOG_ERROR("Introduced vector withou memory allocation.");
        return 2;
    }

    memset(v->components, 0, v->size * sizeof(double));
    if(v->components == NULL){
        LOG_ERROR("Impossible to fill vector with zeros.");
        return 3;
    }
    return 0;
}

int vector_fill(Vector *v, double value)
{
    if (v->size == 0){
        LOG_ERROR("Vector with dimensión 0 introduced.");
        return 1;
    }
    if (v->components == NULL){
        LOG_ERROR("Introduced vector withou memory allocation.");
        return 2;
    }

    memset(v->components, value, v->size * sizeof(double));
    if(v->components == NULL){
        LOG_ERROR("Impossible to fill vector with value %lf.", value);
        return 3;
    }
    return 0;
}

int vector_copy(Vector *dst, const Vector *src)
{
    if (!same_size(dst, src)){
        LOG_ERROR(
            "Vectors introduced with diferent sizes (%d, %d).",
            dst->size,
            src->size
        );
        return 1;
    }
    if (src->components == NULL){
        LOG_ERROR("Introduced source vector (src) withou memory allocation.");
        return 2;
    }

    memcpy(dst->components, src->components, src->size * sizeof(double));
    if (dst->components == NULL){
        return 3;
    }
    return 0;
}


/*
** ------------- BASIC OPERATIONS -------------
*/

int vector_add(Vector *res, const Vector *a, const Vector *b)
{
    if (a->size != b->size || a->size != res->size || b->size != res->size){
        LOG_ERROR(
            "Vectors introduced with diferent sizes (%d, %d, %d).",
            res->size,
            a->size,
            b->size
        );
        return 1;
    }
    if (b->size == 0){
        LOG_ERROR("Vector with dimensión 0 introduced.");
        return 2;
    }

    double *restrict pr = res->components;
    double *restrict pb = b->components;
    double *restrict pa = a->components;
    unsigned n = res->size;

    for (unsigned i = 0; i < n; i++)
    {
        pr[i] = pa[i] + pb[i];
    }

    return 0;
}

int vector_sub(Vector *res, const Vector *a, const Vector *b)
{
    if (a->size != b->size || a->size != res->size || b->size != res->size){
        LOG_ERROR(
            "Vectors introduced with diferent sizes (%d, %d, %d).",
            res->size,
            a->size,
            b->size
        );
        return 1;
    }
    if (b->size == 0){
        LOG_ERROR("Vector with dimensión 0 introduced.");
        return 2;
    }

    double *restrict pr = res->components;
    double *restrict pb = b->components;
    double *restrict pa = a->components;
    unsigned n = res->size;

    for (unsigned i = 0; i < n; i++)
    {
        pr[i] = pa[i] - pb[i];
    }

    return 0;
}

int vector_scale(Vector *res, const Vector *v, double alpha);
double vector_dot(const Vector *a, const Vector *b);
double vector_norm2(const Vector *v);


/*
** ------------- OTHER UTILITY FUNCTIONS -------------
*/

int vector_axpy(Vector *res, double alpha, const Vector *x, const Vector *y);
double vector_max_abs(const Vector *v);
void vector_fill_random(Vector *v, double min, double max);

int vector_resize(Vector *v, unsigned int new_size)
{
    v->size = new_size;
    if (new_size == 0){
        vector_free(v);
    }
    else{
        v->components = realloc(v->components, new_size * sizeof(double));
        if (v->components == NULL){
            LOG_ERROR("Impossible to realloc the memory required.");
            return 1;
        }
    }
    return 0;
}

int set_vector_components(Vector *v, double *components, unsigned int size)
{
    if (size == 0 || size != v->size || !components)
        return 1;

    memcpy(v->components, components, size * sizeof(double));
    return 0;
}


/*
** ------------- AUXILARY FUNCTIONS -------------
*/

void vector_print(const Vector *v);