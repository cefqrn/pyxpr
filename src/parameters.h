#ifndef PARAMETERS_H
#define PARAMETERS_H

// only check whether an expression's values are truthy or not
// (correct must have values of either 0 or 1 if true)
#define CHECK_TRUTHY 1

#define INITIAL (const int []){  2,  3,  4,  5,  6,  7,  8,  9, 10 }
#define CORRECT (const int []){  1,  1,  0,  1,  0,  1,  0,  0,  0 }

#define VALUE_COUNT (sizeof(INITIAL) / sizeof(INITIAL[0]))

#endif