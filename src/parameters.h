#ifndef PARAMETERS_H
#define PARAMETERS_H

// Only check whether an expression's truthiness matches that of the correct values
// 0 is disabled, 1 is enabled
#define CHECK_TRUTHY 1

// Let a solution be a part of future expressions
#define CACHE_SOLUTIONS 0

// Allow numbers other than -9–9
#define CONCAT_NUMBERS 1

#define MAX_LENGTH_SEARCHED 8

// The desired outputs of the expression
// If CHECK_TRUTHY is enabled, the values must be either 0 or 1.
static const int CORRECT[] = {  1,  1,  0,  1,  0,  1,  0,  0,  0 };

#define VALUE_COUNT (sizeof(CORRECT) / sizeof(*CORRECT))

struct variable {
    char *name;
    int values[VALUE_COUNT];
};

// The values at which the variable is evaluated
static const struct variable VARIABLES[] = {
    {
        .name = "x",
        .values = {  2,  3,  4,  5,  6,  7,  8,  9, 10 }
    },
    {
        .name = "y",
        .values = {  4,  5,  6,  7,  8,  9, 10, 11, 12 }
    }
};

#define VARIABLE_COUNT (sizeof(VARIABLES) / sizeof(*VARIABLES))

#endif
