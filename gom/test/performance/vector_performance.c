#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "vector.h"

void sum_performance(unsigned int size)
{
    double time_taken;
    clock_t start_t, end_t;
    Vector v1 = create_vector(size);
    Vector v2 = create_vector(size);
    Vector res = create_vector(size);

    for (unsigned i = 0; i < size; i++)
    {
        v1.components[i] = 1.0;
        v2.components[i] = 2.0;
    }

    printf("Analysing sum_vectors with %u components...\n", size);

    start_t = clock();

    sum_vectors(&res, &v1, &v2);

    end_t = clock();

    time_taken = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Execution time taken: %f seconds (%f ms)\n",
           time_taken, time_taken * 1000);

    free_vector(&v1);
    free_vector(&v2);
    free_vector(&res);
}

int main()
{
    sum_performance(1000);

    sum_performance(10000000);

    return 0;
}