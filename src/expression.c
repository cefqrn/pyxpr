#include "parameters.h"
#include "expression.h"
#include "operator.h"
#include "macros.h"

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Check whether expr's values are correct
bool validate(expression expr) {
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

// Create an expression that always evaluates to value
expression expression_from_constant(int value) {
    expression expr = {
        .precedence = CONSTANT_PRECEDENCE,
        .isValid = true
    };
    snprintf(expr.text, MAX_EXPRESSION_LENGTH, "%d", value);

    for (size_t i=0; i < VALUE_COUNT; ++i)
        expr.values[i] = value;


    return expr;
}

// Use a unary operator on an expression
expression apply(expression expr, operator_unary op) {
    expression newExpr = {
        .precedence = op.precedence,
        .isValid = true
    };
    snprintf(newExpr.text, MAX_EXPRESSION_LENGTH, op.format, expr.text);

    for (size_t i=0; i < VALUE_COUNT; ++i)
        newExpr.values[i] = op.func(expr.values[i]);

    return newExpr;
}

// Combine two expressions with a binary operator
expression combine(expression expr1, expression expr2, operator_binary op) {
    expression newExpr = {
        .precedence = op.precedence,
        .isValid = true
    };
    snprintf(newExpr.text, MAX_EXPRESSION_LENGTH, op.format, expr1.text, expr2.text);

    for (size_t i=0; i < VALUE_COUNT; ++i) {
        // INT_MIN % -1 and INT_MIN / -1 raise arithmetic errors because they overflow
        if ((!expr2.values[i] || (expr1.values[i] == INT_MIN && expr2.values[i] == -1)) && op.hasDivision) {
            newExpr.isValid = false;
            return newExpr;
        }

        newExpr.values[i] = op.func(expr1.values[i], expr2.values[i]);
    }

    return newExpr;
}
