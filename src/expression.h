#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "parameters.h"
#include "operator.h"

#include <stdbool.h>

#define MAX_EXPRESSION_LENGTH 32

struct expression {
    char text[MAX_EXPRESSION_LENGTH];
    int values[VALUE_COUNT];
    int precedence;
    bool allTruthy;
};

bool validate(struct expression expr);

struct expression expression_from_constant(int value);

struct expression apply(struct expression expr, struct operator_unary op);
struct expression combine(struct expression expr1, struct expression expr2, struct operator_binary op);

#endif
