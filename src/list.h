#ifndef LIST_H
#define LIST_H

#include "macros.h"

#include <stdlib.h>

#define LIST_BASE_SIZE 16

typedef struct list_header {
    size_t length;  // Amount of elements in the list
    size_t size;    // Amount of elements the list has access to
} list_header;

#define list_length_of(list) ((list_header *)list - 1)->length
#define list_size_of(list)   ((list_header *)list - 1)->size

// Allocate memory for a list of size LIST_BASE_SIZE
#define list_init(list) { \
    list = (void *)((list_header *)calloc(1, sizeof(list_header) + LIST_BASE_SIZE * sizeof *list) + 1); \
    list_size_of(list) = LIST_BASE_SIZE; \
}
#define list_destroy(list) free((list_header *)list - 1)

// Double the size of the list if the list length is equal to its size
#define list_check_size(list) \
    if (list_length_of(list) == list_size_of(list)) { \
        list_size_of(list) *= 2; \
        list = (void *)((list_header *)realloc(((list_header *)list - 1), sizeof(list_header) + list_size_of(list) * sizeof *list) + 1); \
        CHECK_ALLOC(list, "list"); \
    }

// Increment the length of the list then check whether it should be extended
#define list_length_increment(list) { \
    list_length_of(list)++; \
    list_check_size(list); \
}

// Add a value to the end of the list then check whether it should be extended
#define list_append(list, value) { \
    list[list_length_of(list)] = value; \
    list_length_increment(list); \
}

#endif
