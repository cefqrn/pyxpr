#include "parameters.h"
#include "expression.h"
#include "operator.h"
#include "macros.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Check whether expr's values are correct
bool expression_validate(const expression *expr) {
    #if CHECK_TRUTHY == 1
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if ((expr->values[i] ? true : false) ^ CORRECT[i])
            return false;
    }

    return true;
    #else
    return memcmp(expr->values, CORRECT, sizeof CORRECT) ? false : true;
    #endif
}

// Create an expression that evaluates to the values in INITIAL
expression expression_variable_create() {
    expression expr = {
        .op = OPERATOR_ATOM + VARIABLE,
        .isValid = true
    };

    for (size_t i=0; i < VALUE_COUNT; ++i)
        expr.values[i] = INITIAL[i];

    return expr;
}

// Create an expression that always evaluates to value
expression expression_int_literal_create(int value) {
    expression expr = {
        .op = OPERATOR_ATOM + INT_LITERAL,
        .isValid = true
    };

    for (size_t i=0; i < VALUE_COUNT; ++i)
        expr.values[i] = value;

    return expr;
}

// Set the buffer to the result of a unary operation on the passed expression
void expression_apply(expression *buf, const expression *expr, const operator *op) {
    *buf = (expression){
        .expr1 = expr,
        .op = op,
        .isValid = op->precedence <= expr->op->precedence
    };

    if (buf->isValid)
        op->unaryFunc(buf, expr);
}

// Set the buffer to the result of a binary operation on the passed expressions
void expression_combine(expression *buf, const expression *expr1, const expression *expr2, const operator *op) {
    *buf = (expression){
        .expr1 = expr1,
        .expr2 = expr2,
        .op = op,
        .isValid = op->precedence <= expr1->op->precedence && op->precedence < expr2->op->precedence
    };

    if (buf->isValid)
        op->binaryFunc(buf, expr1, expr2);
}

// Generate the text representation for an expression
void expression_format(char buf[MAX_EXPRESSION_LENGTH], const expression *expr) {
    if (expr->op == OPERATOR_ATOM + INT_LITERAL) {
        snprintf(buf, MAX_EXPRESSION_LENGTH, "%d", *expr->values);
    } else if (expr->op == OPERATOR_ATOM + VARIABLE) {
        snprintf(buf, MAX_EXPRESSION_LENGTH, "x");
    } else if (expr->expr2 == NULL) { // binary operator
        char buf1[MAX_EXPRESSION_LENGTH];

        expression_format(buf1, expr->expr1);

        snprintf(buf, MAX_EXPRESSION_LENGTH, expr->op->format, buf1);
    } else {  // unary operator
        char buf1[MAX_EXPRESSION_LENGTH];
        char buf2[MAX_EXPRESSION_LENGTH];

        expression_format(buf1, expr->expr1);
        expression_format(buf2, expr->expr2);

        snprintf(buf, MAX_EXPRESSION_LENGTH, expr->op->format, buf1, buf2);
    }
}
