#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

Vector create_vector(unsigned size)
{
    Vector v;

    v.size = size;
    v.components = (double *)calloc(size, sizeof(double));

    if (v.components == NULL)
    {
        v.size = 0;
        fprintf(stderr,
                "Error: Not enough memory, returning vector with size 0.\n");
    }

    return v;
}

void vector_zero(Vector *v)
{
    if (v->size > 0 && v->components)
    {
        memset(v->components, 0, v->size * sizeof(double));
    }
}

void vector_resize(Vector *v, unsigned int new_size)
{
    v->size = new_size;
    if (new_size == 0)
        free_vector(v);
    else
        v->components = realloc(v->components, new_size * sizeof(double));
}

void free_vector(Vector *v)
{
    free(v->components);
}

void assign_vector_components(Vector *v, double *components, unsigned int size)
{
    if (size == 0 || size != v->size || !components)
        return;

    memcpy(v->components, components, size * sizeof(double));
}

void sum_vectors(Vector *res, Vector *v, Vector *u)
{
    if (u->size != v->size || u->size != res->size || v->size != res->size)
        return;
    if (v->size == 0)
        return;

    double *restrict pr = res->components;
    double *restrict pv = v->components;
    double *restrict pu = u->components;
    unsigned n = res->size;

    for (unsigned i = 0; i < n; i++)
    {
        pr[i] = pv[i] + pu[i];
    }
}