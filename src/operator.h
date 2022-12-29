#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOKEN_FORMAT_LENGTH 8

#define VARIABLE_PRECEDENCE 16
#define CONSTANT_PRECEDENCE 17

typedef struct operator_unary {
    char format[MAX_TOKEN_FORMAT_LENGTH];
    int (*func)(int);
    size_t length;
    int precedence;
} operator_unary;

typedef struct operator_binary {
    char format[MAX_TOKEN_FORMAT_LENGTH];
    int (*func)(int, int);
    size_t length;
    int precedence;
    bool requiresTruthySecondExpression;
} operator_binary;

operator_unary paren_operator;
operator_unary invert_operator;
operator_unary negate_operator;

operator_binary exponentiation_operator;
operator_binary mul_operator;
operator_binary fdiv_operator;
operator_binary mod_operator;
operator_binary add_operator;
operator_binary sub_operator;
operator_binary band_operator;
operator_binary xor_operator;
operator_binary bor_operator;
operator_binary lt_operator;
operator_binary le_operator;
operator_binary gt_operator;
operator_binary ge_operator;
operator_binary ne_operator;
operator_binary eq_operator;

// Array of unary operators in reverse order of precedence
#define UNARY_OPERATORS (const operator_unary []){ \
    negate_operator, \
    invert_operator, \
    paren_operator, \
}

// Array of binary operators in reverse order of precedence
#define BINARY_OPERATORS (const operator_binary []){ \
    lt_operator, \
    le_operator, \
    gt_operator, \
    ge_operator, \
    ne_operator, \
    eq_operator, \
    bor_operator, \
    xor_operator, \
    band_operator, \
    sub_operator, \
    add_operator, \
    fdiv_operator, \
    mod_operator, \
    mul_operator, \
    exponentiation_operator, \
}

#define UNARY_OPERATOR_COUNT sizeof(UNARY_OPERATORS) / sizeof(UNARY_OPERATORS[0])
#define BINARY_OPERATOR_COUNT sizeof(BINARY_OPERATORS) / sizeof(BINARY_OPERATORS[0])

#endif
