#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "parameters.h"

#include <stdbool.h>
#include <stdlib.h>

#define HASHTABLE_BASE_SIZE 16

// How much of the table needs to be filled before it's extended
#define HASHTABLE_MAX_LOAD_PERCENTAGE 60

typedef struct hashtable hashtable_h;

hashtable_h *hashtable_create(void);
void         hashtable_destroy(hashtable_h *table);

bool hashtable_insert_if_higher(hashtable_h **table, const int key[VALUE_COUNT], int value);

#endif
