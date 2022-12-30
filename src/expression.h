#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "parameters.h"
#include "operator.h"

#include <stdbool.h>

#define MAX_EXPRESSION_LENGTH MAX_LENGTH_SEARCHED + 1

typedef struct expression {
    char text[MAX_EXPRESSION_LENGTH];
    int values[VALUE_COUNT];
    int precedence;
    bool isValid;
} expression;

bool validate(expression expr);
bool expression_eq(expression newExpr, expression baseExpr);

expression expression_from_constant(int value);

expression apply(expression expr, operator_unary op);
expression combine(expression expr1, expression expr2, operator_binary op);

#endif
