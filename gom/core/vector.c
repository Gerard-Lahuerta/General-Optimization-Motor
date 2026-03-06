
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
** ------------- VECTOR CREATION -------------
*/

int vector_init(Vector *v, unsigned int size)
{
    v->size = size;
    if (size == 0){
        LOG_WARN("Introduced vector with size 0.");
    }
    else{
        size_t n_bytes = size * sizeof(double);
        size_t padded_size = (n_bytes + 63) & ~63;

        v->components = (double *)aligned_alloc(64, padded_size);

        if (v->components == NULL)
        {
            v->size = 0;
            LOG_ERROR("Not enough memory, vector size set to 0.");
            return 1;
        }

        memset(v->components, 0, padded_size);
    }
    return 0;
}

void vector_free(Vector *v)
{
    free(v->components);
}

/*
** ------------- OTHER UTILITY FUNCTIONS -------------
*/
void vector_fill_random(Vector *v, double min, double max);

double vector_max_abs(const Vector *v);

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

void vector_print(const Vector *v) {
    if (v == NULL){
        printf(ANSI_YEL " - NULL - " ANSI_RESET);
        return;
    };

    char* vector_text = (char*) malloc(v->size * 20 * sizeof(char));
    vector_text[0] = '\0';

    for (unsigned int i = 0; i < v->size; i++) {
        char buffer[32];

        sprintf(buffer, "%.2f ", v->components[i]);
        strcat(vector_text, buffer);
    }

    fprintf(stdout, "%s\n", vector_text);

    free(vector_text);
}