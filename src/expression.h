#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "parameters.h"
#include "operator.h"

#include <stdbool.h>
#include <stdlib.h>

#define MAX_EXPRESSION_LENGTH MAX_LENGTH_SEARCHED + 1

typedef struct expression {
    int values[VALUE_COUNT];
    const struct expression *expr1;
    const struct expression *expr2;
    const operator *op;
    bool isValid;
} expression;

void expression_format(char buf[MAX_EXPRESSION_LENGTH], const expression *expr);

bool expression_validate(expression *expr);

expression expression_variable_create();
expression expression_int_literal_create(int value);

void expression_apply(expression *buf, const expression *expr, const operator *op);
void expression_combine(expression *buf, const expression *expr1, const expression *expr2, const operator *op);

#endif
