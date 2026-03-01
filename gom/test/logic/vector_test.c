#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vector.h"

#define CLR_RED     "\x1b[31m"
#define CLR_GREEN   "\x1b[32m"
#define CLR_RESET   "\x1b[0m"

#define ICON_CHECK  "✔"
// #define ICON_CROSS  "✘"

int double_eq(double a, double b) {
    return fabs(a - b) < 1e-9;
}

void test_vector_creation() {
    printf("Executing: test_vector_creation... ");
    Vector v = create_vector(10);
    assert(v.size == 10);
    assert(v.components != NULL);

    for(int i = 0; i < 10; i++) {
        assert(v.components[i] == 0.0);
    }

    free_vector(&v);
    printf("%s %s VECTOR CREATION TEST PASSED%s\n",
        CLR_GREEN, ICON_CHECK, CLR_RESET);
}

void test_vector_sum() {
    printf("Executing: test_vector_sum... ");
    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};

    Vector v1 = create_vector(3);
    Vector v2 = create_vector(3);
    Vector res = create_vector(3);

    assign_vector_components(&v1, data1, 3);
    assign_vector_components(&v2, data2, 3);

    sum_vectors(&res, &v1, &v2);

    assert(double_eq(res.components[0], 5.0));
    assert(double_eq(res.components[1], 7.0));
    assert(double_eq(res.components[2], 9.0));

    free_vector(&v1); free_vector(&v2); free_vector(&res);
    printf("%s %s VECTOR SUM FUNCTION PASSED%s\n",
        CLR_GREEN, ICON_CHECK, CLR_RESET);
}

int main() {
    printf("--- START OF AUTOMATIC VECTOR FUNCTIONS TESTS ---\n");
    test_vector_creation();
    test_vector_sum();

    printf("--- ALL VECTOR TESTS HAVE BEEN DONE ---\n");
    return 0;
}