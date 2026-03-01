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
    Vector v;
    vector_init(&v, 10);
    assert(v.size == 10);
    assert(v.components != NULL);

    for(int i = 0; i < 10; i++) {
        assert(v.components[i] == 0.0);
    }

    vector_free(&v);
    printf("%s %s VECTOR CREATION TEST PASSED%s\n",
        CLR_GREEN, ICON_CHECK, CLR_RESET);
}

void test_vector_add() {
    printf("Executing: test_vector_add... ");
    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};

    Vector v1, v2, res;
    vector_init(&v1, 3);
    vector_init(&v2, 3);
    vector_init(&res, 3);

    set_vector_components(&v1, data1, 3);
    set_vector_components(&v2, data2, 3);

    vector_add(&res, &v1, &v2);

    assert(double_eq(res.components[0], 5.0));
    assert(double_eq(res.components[1], 7.0));
    assert(double_eq(res.components[2], 9.0));

    vector_free(&v1); vector_free(&v2); vector_free(&res);
    printf("%s %s VECTOR ADD FUNCTION PASSED%s\n",
        CLR_GREEN, ICON_CHECK, CLR_RESET);
}

void test_vector_sub() {
    printf("Executing: test_vector_sub... ");
    double data1[] = {4.0, 5.0, 6.0};
    double data2[] = {3.0, 2.0, 1.0};

    Vector v1, v2, res;
    vector_init(&v1, 3);
    vector_init(&v2, 3);
    vector_init(&res, 3);

    set_vector_components(&v1, data1, 3);
    set_vector_components(&v2, data2, 3);

    vector_sub(&res, &v1, &v2);

    assert(double_eq(res.components[0], 1.0));
    assert(double_eq(res.components[1], 3.0));
    assert(double_eq(res.components[2], 5.0));

    vector_free(&v1); vector_free(&v2); vector_free(&res);
    printf("%s %s VECTOR SUBSTRACT FUNCTION PASSED%s\n",
        CLR_GREEN, ICON_CHECK, CLR_RESET);
}

int main() {
    printf("--- START OF AUTOMATIC VECTOR FUNCTIONS TESTS ---\n");
    test_vector_creation();
    test_vector_add();
    test_vector_sub();

    printf("--- ALL VECTOR TESTS HAVE BEEN DONE ---\n");
    return 0;
}