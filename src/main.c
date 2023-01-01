#include "expression.h"
#include "parameters.h"
#include "hashtable.h"
#include "operator.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>

void print_solution(expression *solution, size_t length) {
    char buf[MAX_EXPRESSION_LENGTH];
    expression_format(buf, solution);

    printf("Found solution of length %zu: %s\n", length, buf);
}

int main() {
    // Hash table that holds the highest precedence of all the expressions with identical values
    hashtable *cache = hashtable_create();

    // Array of lists of expressions whose indices are equal to the length of the expressions they contain
    list_of(expression) *expressions[MAX_EXPRESSION_LENGTH];
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i)
        expressions[i] = list_create(expressions[i]);

    // Add variable that takes the values of INITIAL
    list_append(expressions[1], expression_variable_create());

    // Add integer literals from 0 through 9
    for (size_t i=0; i < 10; ++i)
        list_append(expressions[1], expression_int_literal_create(i));

    for (size_t i=0; i < expressions[1]->length; ++i)
        hashtable_insert_if_higher(&cache, expressions[1]->data[i].values, expressions[1]->data[i].op->precedence);

    for (size_t newExprLength=1; newExprLength < MAX_EXPRESSION_LENGTH; ++newExprLength) {
        printf("Finding expressions of length %zu...\n", newExprLength);

        for (size_t i=0; i < OPERATOR_UNARY_COUNT; ++i) {
            const operator *op = OPERATOR_UNARY + i;
            int exprLength = newExprLength - op->length;

            if (exprLength < 1)
                continue;

            for (size_t j=0; j < expressions[exprLength]->length; ++j) {
                expression *expr = expressions[exprLength]->data + j;

                // Overwrite the last element in the list until it's valid
                expression *newExpr = expressions[newExprLength]->data + expressions[newExprLength]->length;
                expression_apply(newExpr, expr, op);
                if (!newExpr->isValid)
                    continue;

                if (expression_validate(newExpr))
                    print_solution(newExpr, newExprLength);

                // Don't store the expression if this is the last loop
                // or if the expression is equivalent to a previous one
                if (newExprLength != MAX_LENGTH_SEARCHED && hashtable_insert_if_higher(&cache, newExpr->values, op->precedence)) {
                    expressions[newExprLength]->length++;
                    list_check_length(expressions[newExprLength]);
                }
            }
        }

        for (size_t i=0; i < OPERATOR_BINARY_COUNT; ++i) {
            const operator *op = OPERATOR_BINARY + i;
            int remainingLength = newExprLength - op->length;

            if (remainingLength < 2)
                continue;

            for (size_t expr1Length=1; expr1Length < (size_t)remainingLength; ++expr1Length) {
                size_t expr2Length = remainingLength - expr1Length;

                for (size_t j=0; j < expressions[expr1Length]->length; ++j) {
                    expression *expr1 = expressions[expr1Length]->data + j;
                    for (size_t k=0; k < expressions[expr2Length]->length; ++k) {
                        expression *expr2 = expressions[expr2Length]->data + k;

                        expression *newExpr = expressions[newExprLength]->data + expressions[newExprLength]->length;
                        expression_combine(newExpr, expr1, expr2, op);
                        if (!newExpr->isValid)
                            continue;

                        if (expression_validate(newExpr))
                            print_solution(newExpr, newExprLength);

                        if (newExprLength != MAX_LENGTH_SEARCHED && hashtable_insert_if_higher(&cache, newExpr->values, op->precedence)) {
                            expressions[newExprLength]->length++;
                            list_check_length(expressions[newExprLength]);
                        }
                    }
                }
            }
        }

        printf("Stored %zu expressions\n", expressions[newExprLength]->length);
    }

    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i)
        list_destroy(expressions[i]);

    hashtable_destroy(cache);
}
