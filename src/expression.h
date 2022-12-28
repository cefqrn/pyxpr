#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "parameters.h"
#include "operator.h"

#include <stdbool.h>
#include <stdlib.h>

#define MAX_EXPRESSION_LENGTH 32

struct expression {
    char text[MAX_EXPRESSION_LENGTH];
    int values[VALUE_COUNT];
    int precedence;
    bool allTruthy;
};

bool validate(struct expression *expr);

struct expression *expression_from_constant(int value);

struct expression *apply(const struct expression *expr, const struct operator_unary *op);
struct expression *combine(const struct expression *expr1, const struct expression *expr2, const struct operator_binary *op);

void expression_free(struct expression *expr);

#endif
