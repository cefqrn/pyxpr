#ifndef OPERATOR_H
#define OPERATOR_H

#include "expression.h"

#include <stdio.h>

struct expression;

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
        void (*unaryFunc )(struct expression *, const struct expression *);
        void (*binaryFunc)(struct expression *, const struct expression *, const struct expression *);
    };
    size_t length;
    int precedence;
} operator;

const operator OPERATOR_ATOM[OPERATOR_ATOM_COUNT];
const operator OPERATOR_UNARY[OPERATOR_UNARY_COUNT];
const operator OPERATOR_BINARY[OPERATOR_BINARY_COUNT];

#endif
