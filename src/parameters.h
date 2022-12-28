#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdlib.h>

// only check whether an expression's values are truthy or not
// (correct must have values of either 0 or 1 if true)
#define CHECK_TRUTHY

#define VALUE_COUNT 9

extern int initial[VALUE_COUNT];
extern int correct[VALUE_COUNT];

#endif