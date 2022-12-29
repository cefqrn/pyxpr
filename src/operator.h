#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOKEN_FORMAT_LENGTH 8

#define VARIABLE_PRECEDENCE 16
#define CONSTANT_PRECEDENCE 17

struct operator_unary {
    char format[MAX_TOKEN_FORMAT_LENGTH];
    int (*func)(int);
    size_t length;
    int precedence;
};

struct operator_binary {
    char format[MAX_TOKEN_FORMAT_LENGTH];
    int (*func)(int, int);
    size_t length;
    int precedence;
    bool requiresTruthySecondExpression;
};

struct operator_unary paren_operator;
struct operator_unary invert_operator;
struct operator_unary negate_operator;

struct operator_binary exponentiation_operator;
struct operator_binary mul_operator;
struct operator_binary fdiv_operator;
struct operator_binary mod_operator;
struct operator_binary add_operator;
struct operator_binary sub_operator;
struct operator_binary band_operator;
struct operator_binary xor_operator;
struct operator_binary bor_operator;
struct operator_binary lt_operator;
struct operator_binary le_operator;
struct operator_binary gt_operator;
struct operator_binary ge_operator;
struct operator_binary ne_operator;
struct operator_binary eq_operator;

// array of unary operators in reverse order of precedence
#define UNARY_OPERATORS (const struct operator_unary []){ \
    negate_operator, \
    invert_operator, \
    paren_operator, \
}

// array of binary operators in reverse order of precedence
#define BINARY_OPERATORS (const struct operator_binary []){ \
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
