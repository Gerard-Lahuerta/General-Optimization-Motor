#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "vector.h"

void add_performance(unsigned int size)
{
    double time_taken;
    clock_t start_t, end_t;
    Vector v1, v2, res;
    vector_init(&v1, size);
    vector_init(&v2, size);
    vector_init(&res, size);

    for (unsigned i = 0; i < size; i++)
    {
        v1.components[i] = 1.0;
        v2.components[i] = 2.0;
    }

    printf("Analysing vector_add with %u components...\n", size);

    start_t = clock();

    vector_add(&res, &v1, &v2);

    end_t = clock();

    time_taken = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Execution time taken: %f seconds (%f ms)\n",
           time_taken, time_taken * 1000);

    vector_free(&v1);
    vector_free(&v2);
    vector_free(&res);
}

void sub_performance(unsigned int size)
{
    double time_taken;
    clock_t start_t, end_t;
    Vector v1, v2, res;
    vector_init(&v1, size);
    vector_init(&v2, size);
    vector_init(&res, size);

    for (unsigned i = 0; i < size; i++)
    {
        v1.components[i] = 1.0;
        v2.components[i] = 2.0;
    }

    printf("Analysing vector_sub with %u components...\n", size);

    start_t = clock();

    vector_sub(&res, &v1, &v2);

    end_t = clock();

    time_taken = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Execution time taken: %f seconds (%f ms)\n",
           time_taken, time_taken * 1000);

    vector_free(&v1);
    vector_free(&v2);
    vector_free(&res);
}

int main()
{
    unsigned int low_size = 1000;
    unsigned int high_size = 10000000;

    add_performance(low_size);
    add_performance(high_size);

    sub_performance(low_size);
    sub_performance(high_size);

    return 0;
}