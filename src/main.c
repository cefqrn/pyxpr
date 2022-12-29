#include "parameters.h"
#include "expression.h"
#include "operator.h"
#include "list.h"

#include <string.h>
#include <stdio.h>

/*
don't forget about operator precedence!
if something has higher precedence, don't use it!
it'll appear anyways from the other direction
~5/2 shouldn't come from 5/2
it should come from ~5
*/

int main() {
    // array of lists
    // index = length of expression
    list_of(expression) *expressions[MAX_EXPRESSION_LENGTH];
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        expressions[i] = list_create(expression);
    }

    expression var = {
        .text = "x",
        .precedence = VARIABLE_PRECEDENCE
    };

    memcpy(var.values, INITIAL, sizeof INITIAL);

    // add variable
    list_append(expressions[strnlen(var.text, MAX_EXPRESSION_LENGTH)], var);

    // add int literals
    for (size_t i=0; i < 10; ++i) {
        list_append(expressions[1], expression_from_constant(i));
    }

    expression solution;
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

                if (exprLength + op.length > MAX_EXPRESSION_LENGTH - 1)
                    continue;

                expression newExpr = apply(expr, op);

                if (validate(newExpr)) {
                    solution = newExpr;
                    goto EXIT;
                }

                list_append(expressions[exprLength], newExpr);
            }
        }

        for (size_t i=0; i < BINARY_OPERATOR_COUNT; ++i) {
            operator_binary op = BINARY_OPERATORS[i];
            int maxRemainingLength = exprLength - op.length;

            if (maxRemainingLength < 2)
                continue;

            for (size_t expr1Length=1; expr1Length < maxRemainingLength; ++expr1Length) {
                int expr2Length = exprLength - expr1Length - op.length;

                list_foreach(expression expr1, expressions[expr1Length]) {
                    if (op.precedence > expr1.precedence)
                        continue;

                    list_foreach(expression expr2, expressions[expr2Length]) {
                        if (op.precedence >= expr2.precedence)
                            continue;

                        if (op.requiresTruthySecondExpression && !expr2.allTruthy)
                            continue;

                        expression newExpr = combine(expr1, expr2, op);

                        if (validate(newExpr)) {
                            solution = newExpr;
                            goto EXIT;
                        }

                        list_append(expressions[exprLength], newExpr);
                    }
                }
            }
        }

        printf("Found %zu\n", expressions[exprLength]->length);
    }

    EXIT:
    printf("%s\n", solution.text);

    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        list_free(expressions[i]);
    }
}
