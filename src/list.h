#ifndef LIST_H
#define LIST_H

#include "macros.h"

#include <stdlib.h>

#define list_of(type) struct { \
    size_t length; \
    type data[]; \
}

// Allocate memory for a list of size of 1
#define list_create(list) calloc(1, sizeof(*list) + 1 * sizeof(*list->data))
#define list_destroy(list) free(list)

// Double the size of the list if the list length is a power of 2
#define list_check_length(list) \
    if (!(list->length & (list->length - 1))) { \
        list = realloc(list, sizeof(*list) + 2 * list->length * sizeof(*list->data)); \
        CHECK_ALLOC(list, "more expressions"); \
    }

// Add a value to the list then check if the list should be extended
#define list_append(list, value) { \
    list->data[list->length++] = value; \
    list_check_length(list); \
}

#endif
