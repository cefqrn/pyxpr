#ifndef PARAMETERS_H
#define PARAMETERS_H

// Only check whether an expression's truthiness matches that of the correct values
// 0 is disabled, 1 is enabled
#define CHECK_TRUTHY 1

#define MAX_LENGTH_SEARCHED 8

// The values at which the variable is evaluated
#define INITIAL (const int []){  2,  3,  4,  5,  6,  7,  8,  9, 10 }

// The desired outputs of the expression
// If CHECK_TRUTHY is 1, the values must be either 0 or 1.
#define CORRECT (const int []){  1,  1,  0,  1,  0,  1,  0,  0,  0 }

#define VALUE_COUNT (sizeof(INITIAL) / sizeof(*INITIAL))

#endif
