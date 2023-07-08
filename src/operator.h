#ifndef OPERATOR_H
#define OPERATOR_H

#include "parameters.h"

#include <stdbool.h>
#include <stdlib.h>

#define COMPARISON_PRECEDENCE 4
#define INT_LITERAL_PRECEDENCE 17

typedef enum operator_atom_type {
    VARIABLE,
    INT_LITERAL,
    OPERATOR_ATOM_COUNT
} operator_atom_type;

typedef enum operator_unary_type {
    PAREN_OPERATOR,
    INV_OPERATOR,
    NEG_OPERATOR,
    OPERATOR_UNARY_COUNT
} operator_unary_type;

typedef enum operator_binary_type {
    #if CONCAT_NUMBERS == 1
    CONCAT_NUMBER,
    #endif
    POW_OPERATOR,
    MUL_OPERATOR,
    FDIV_OPERATOR,
    MOD_OPERATOR,
    ADD_OPERATOR,
    SUB_OPERATOR,
    BAND_OPERATOR,
    XOR_OPERATOR,
    BOR_OPERATOR,
    LT_OPERATOR,
    LE_OPERATOR,
    GT_OPERATOR,
    GE_OPERATOR,
    NE_OPERATOR,
    EQ_OPERATOR,
    OPERATOR_BINARY_COUNT
} operator_binary_type;

typedef struct operator {
    char const *format;
    union {
        bool (*unaryFunc )(int *restrict, const int *);
        bool (*binaryFunc)(int *restrict, const int *, const int *);
    };
    bool (*chainedFunc)(int *restrict, const int *, const int *, const int *);
    size_t length;
    int precedence;
} operator;

const operator OPERATOR_ATOM[OPERATOR_ATOM_COUNT];
const operator OPERATOR_UNARY[OPERATOR_UNARY_COUNT];
const operator OPERATOR_BINARY[OPERATOR_BINARY_COUNT];

#endif
