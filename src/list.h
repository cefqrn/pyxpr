#ifndef LIST_H
#define LIST_H

#include "macros.h"

#include <stdlib.h>

#define list_of(type) struct { \
    size_t length; \
    type data[]; \
}

// Allocate memory for a list of size of 1
#define list_create(type) calloc(1, sizeof(list_of(type)) + 1 * sizeof(type))
#define list_free(list) free(list)

// Double the size of the list if the list length is a power of 2
#define list_check_length(list) \
    if (!(list->length & (list->length - 1))) { \
        list = realloc(list, sizeof(*list) + 2 * list->length * sizeof(*list->data)); \
        CHECK_ALLOC(list, "more expressions"); \
    }

#define list_append(list, value) { \
    list->data[list->length++] = value; \
    list_check_length(list); \
}

#define list_foreach(element, list) \
    for (int _i=0, _j=1; _i < list->length; ++_i, _j=1) \
        for (element=list->data[_i]; _j; _j=!_j)

#endif
