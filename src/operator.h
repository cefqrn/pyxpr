#ifndef OPERATOR_H
#define OPERATOR_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOKEN_FORMAT_LENGTH 8

#define VARIABLE_PRECEDENCE 16
#define CONSTANT_PRECEDENCE 17

#define UNARY_OPERATOR_COUNT 3
#define BINARY_OPERATOR_COUNT 15

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

struct operator_unary *UNARY_OPERATORS[UNARY_OPERATOR_COUNT];
struct operator_binary *BINARY_OPERATORS[BINARY_OPERATOR_COUNT];

#endif
