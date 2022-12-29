#include "parameters.h"
#include "expression.h"
#include "operator.h"
#include "macros.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// check if values is identical to correctValues
bool validate(struct expression expr) {
    #if CHECK_TRUTHY == 1
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if ((expr.values[i] ? true : false) ^ CORRECT[i])
            return false;
    }

    return true;
    #else
    return memcmp(expr.values, CORRECT, sizeof CORRECT) ? false : true;
    #endif
}

// generate an expression from a constant value
struct expression expression_from_constant(int value) {
    struct expression expr = {
        .precedence = CONSTANT_PRECEDENCE,
        .allTruthy = value ? true : false
    };

    for (size_t i=0; i < VALUE_COUNT; ++i) {
        expr.values[i] = value;
    }

    snprintf(expr.text, MAX_EXPRESSION_LENGTH, "%d", value);

    return expr;
}

// use a unary operator on an expression
struct expression apply(struct expression expr, struct operator_unary op) {
    struct expression newExpr = {
        .precedence = op.precedence
    };

    snprintf(newExpr.text, MAX_EXPRESSION_LENGTH, op.format, expr.text);

    for (size_t i=0; i < VALUE_COUNT; ++i) {
        int value = op.func(expr.values[i]);

        newExpr.values[i] = value;
        newExpr.allTruthy &= value ? true : false;
    }

    return newExpr;
}

// combine two expressions using a binary operator
struct expression combine(struct expression expr1, struct expression expr2, struct operator_binary op) {
    struct expression newExpr = {
        .precedence = op.precedence,
        .allTruthy = true
    };

    snprintf(newExpr.text, MAX_EXPRESSION_LENGTH, op.format, expr1.text, expr2.text);

    
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        int value = op.func(expr1.values[i], expr2.values[i]);

        newExpr.values[i] = value;
        newExpr.allTruthy &= value ? true : false;
    }

    return newExpr;
}
