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
    struct expression var = {
        .text = "x",
        .precedence = VARIABLE_PRECEDENCE
    };

    memcpy(var.values, INITIAL, sizeof INITIAL);

    // array of lists
    // index + 1 = length of expression
    struct list *expressions[MAX_EXPRESSION_LENGTH];
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        expressions[i] = list_create();
    }

    // add variable
    list_append(expressions[strnlen(var.text, MAX_EXPRESSION_LENGTH)], &var);

    // add int literals
    for (size_t i=0; i < 10; ++i) {
        list_append(expressions[1], expression_from_constant(i));
    }

    struct expression *solution = NULL;
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i) {
        printf("Finding expressions of length %zu...\n", i);

        for (size_t j=0; j < UNARY_OPERATOR_COUNT; ++j) {
            struct operator_unary *op = UNARY_OPERATORS[j];
            int requiredExprLength = i - op->length;

            if (requiredExprLength < 1)
                continue;

            struct list_node *curr = expressions[requiredExprLength]->first;
            while (curr != NULL) {
                struct expression *currExpr = curr->value;
                curr = curr->next;

                if (op->precedence > currExpr->precedence)
                    break;

                if (i + op->length > MAX_EXPRESSION_LENGTH - 1)
                    continue;

                struct expression *newExpr = apply(currExpr, op);

                if (validate(newExpr)) {
                    solution = newExpr;
                    goto EXIT;
                }

                list_append(expressions[i], newExpr);
            }
        }

        for (size_t j=0; j < BINARY_OPERATOR_COUNT; ++j) {
            struct operator_binary *op = BINARY_OPERATORS[j];
            int maxRemainingLength = i - op->length;

            if (maxRemainingLength < 2)
                continue;

            for (size_t k=1; k < maxRemainingLength; ++k) {
                int requiredExpr2Length = i - k - op->length;

                struct list_node *curr1 = expressions[k]->first;
                while (curr1 != NULL) {
                    struct expression *expr1 = curr1->value;
                    curr1 = curr1->next;

                    if (op->precedence > expr1->precedence)
                        continue;

                    struct list_node *curr2 = expressions[requiredExpr2Length]->first;
                    while (curr2 != NULL) {
                        struct expression *expr2 = curr2->value;
                        curr2 = curr2->next;

                        // order of operations
                        if (op->precedence >= expr2->precedence)
                            continue;

                        if (op->requiresTruthySecondExpression && !expr2->allTruthy)
                            continue;

                        struct expression *newExpr = combine(expr1, expr2, op);

                        if (validate(newExpr)) {
                            solution = newExpr;
                            goto EXIT;
                        }

                        list_append(expressions[i], newExpr);
                    }
                }
            }
        }

        printf("Found %zu\n", expressions[i]->length);
    }

    EXIT:
    printf("%s\n", solution->text);
}
