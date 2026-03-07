
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
#include "error.h"

/*
** ------------- VECTOR CREATION -------------
*/

int vector_init(Vector *v, unsigned int size)
{
    v->size = size;
    if(CHECK_W(size != 0, VEC_WARN_DIM_0)){
        size_t n_bytes = size * sizeof(double);
        size_t padded_size = (n_bytes + 63) & ~63;

        v->components = (double *)aligned_alloc(64, padded_size);

        ASSERT_ERROR(!v->components, ERR_NULL);

        memset(v->components, 0, padded_size);
    }
    return 0;
}

int vector_free(Vector *v)
{
    if(CHECK_W(v && v->components, VEC_WARN_DIM_0)){
        free(v->components);
    }
    v->size = 0;
    return 0;
}

/*
** ------------- OTHER UTILITY FUNCTIONS -------------
*/
int vector_fill_random(Vector *v, double min, double max);

int vector_resize(Vector *v, unsigned int new_size)
{
    v->size = new_size;
    if (new_size == 0){
        vector_free(v);
    }
    else{
        v->components = realloc(v->components, new_size * sizeof(double));
        ASSERT_ERROR(!v->components, ERR_MALLOC);
    }
    return 0;
}

int set_vector_components(Vector *v, double *components, unsigned int size)
{
    ASSERT_ERROR(!v || !v->components, VEC_ERR_NULL);
    ASSERT_ERROR(!components, ERR_NULL);
    ASSERT_ERROR(size == 0, ERR_PARAM_VALUE);

    memcpy(v->components, components, size * sizeof(double));
    ASSERT_ERROR(!v->components, ERR_MALLOC);
    return 0;
}


/*
** ------------- AUXILARY FUNCTIONS -------------
*/

int vector_print(const Vector *v) {
    ASSERT_ERROR(!v || !v->components, VEC_ERR_NULL);
    ASSERT_ERROR(v->size == 0, VEC_ERR_DIM_0);

    char* vector_text = (char*) malloc(v->size * 20 * sizeof(char));
    vector_text[0] = '\0';

    for (unsigned int i = 0; i < v->size; i++) {
        char buffer[32];

        sprintf(buffer, "%.2f ", v->components[i]);
        strcat(vector_text, buffer);
    }

    fprintf(stdout, "%s\n", vector_text);

    free(vector_text);
    return 0;
}