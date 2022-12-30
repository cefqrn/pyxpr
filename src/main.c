#include "parameters.h"
#include "expression.h"
#include "operator.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_solution(expression solution, size_t length) {
    printf("Found solution of length %zu: %s\n", length, solution.text);
}

int main() {
    // Array of lists of expressions whose indices are equal to the length of the expressions they contain
    list_of(expression) *expressions[MAX_EXPRESSION_LENGTH];
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        expressions[i] = list_create(expression);
    }

    // Variable that takes the values of INITIAL
    expression var = {
        .text = "x",
        .precedence = VARIABLE_PRECEDENCE
    };

    memcpy(var.values, INITIAL, sizeof INITIAL);

    list_append(expressions[strnlen(var.text, MAX_EXPRESSION_LENGTH)], var);

    // Add integer literals from 0 through 9
    for (size_t i=0; i < 10; ++i) {
        list_append(expressions[1], expression_from_constant(i));
    }

    for (size_t exprLength=1; exprLength < MAX_EXPRESSION_LENGTH; ++exprLength) {
        printf("Finding expressions of length %zu...\n", exprLength);

        for (size_t i=0; i < UNARY_OPERATOR_COUNT; ++i) {
            operator_unary op = UNARY_OPERATORS[i];
            int requiredExprLength = exprLength - op.length;

            if (requiredExprLength < 1)
                continue;

            list_foreach(expression expr, expressions[requiredExprLength]) {
                if (op.precedence > expr.precedence)
                    break;

                expression newExpr = apply(expr, op);

                if (validate(newExpr))
                    print_solution(newExpr, exprLength);

                if (exprLength != MAX_LENGTH_SEARCHED && !expression_eq(newExpr, expr))
                    list_append(expressions[exprLength], newExpr);
            }
        }

        for (size_t i=0; i < BINARY_OPERATOR_COUNT; ++i) {
            operator_binary op = BINARY_OPERATORS[i];
            int remainingLength = exprLength - op.length;

            if (remainingLength < 2)
                continue;

            for (size_t expr1Length=1; expr1Length < remainingLength; ++expr1Length) {
                int expr2Length = remainingLength - expr1Length;

                list_foreach(expression expr1, expressions[expr1Length]) {
                    if (op.precedence > expr1.precedence)
                        continue;

                    list_foreach(expression expr2, expressions[expr2Length]) {
                        if (op.precedence >= expr2.precedence)
                            continue;

                        expression newExpr = combine(expr1, expr2, op);
                        if (!newExpr.isValid)
                            continue;

                        if (validate(newExpr))
                            print_solution(newExpr, exprLength);

                        if (exprLength != MAX_LENGTH_SEARCHED && !expression_eq(newExpr, expr1) && !expression_eq(newExpr, expr2))
                            list_append(expressions[exprLength], newExpr);
                    }
                }
            }
        }

        printf("Cached %zu expressions\n", expressions[exprLength]->length);
    }

    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        list_free(expressions[i]);
    }
}
