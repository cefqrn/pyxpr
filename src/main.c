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
    hashtable_h *cache = hashtable_create();

    // Array of lists of expressions whose indices are equal to the length of the expressions they contain
    expression *expressions[MAX_EXPRESSION_LENGTH];
    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i)
        list_init(expressions[i]);

    // Add variable that takes the values of INITIAL
    list_append(expressions[1], expression_variable_create());

    // Add integer literals from 0 through 9
    for (size_t i=0; i < 10; ++i)
        list_append(expressions[1], expression_int_literal_create(i));

    for (size_t i=0; i < list_length_of(expressions[1]); ++i)
        hashtable_insert_if_higher(&cache, expressions[1][i].values, expressions[1][i].op->precedence);

    for (size_t newExprLength=1; newExprLength < MAX_EXPRESSION_LENGTH; ++newExprLength) {
        printf("Finding expressions of length %zu...\n", newExprLength);

        for (size_t i=0; i < OPERATOR_UNARY_COUNT; ++i) {
            const operator *op = OPERATOR_UNARY + i;
            int exprLength = newExprLength - op->length;

            if (exprLength < 1)
                continue;

            for (size_t j=0; j < list_length_of(expressions[exprLength]); ++j) {
                const expression *expr = expressions[exprLength] + j;

                // Overwrite the last element in the list until it's valid
                expression *newExpr = expressions[newExprLength] + list_length_of(expressions[newExprLength]);
                if (!expression_apply(newExpr, expr, op))
                    continue;

                if (expression_validate(newExpr)) {
                    print_solution(newExpr, newExprLength);
                    #if CACHE_SOLUTIONS == 0
                    continue;
                    #endif
                }

                // Don't store the expression if this is the last loop
                // or if the expression is equivalent to a previous one
                if (newExprLength != MAX_LENGTH_SEARCHED && hashtable_insert_if_higher(&cache, newExpr->values, op->precedence))
                    list_length_increment(expressions[newExprLength]);
            }
        }

        for (size_t i=0; i < OPERATOR_BINARY_COUNT; ++i) {
            const operator *op = OPERATOR_BINARY + i;
            int remainingLength = newExprLength - op->length;

            if (remainingLength < 2)
                continue;

            for (size_t expr1Length=1; expr1Length < (size_t)remainingLength; ++expr1Length) {
                size_t expr2Length = remainingLength - expr1Length;

                for (size_t j=0; j < list_length_of(expressions[expr1Length]); ++j) {
                    const expression *expr1 = expressions[expr1Length] + j;
                    for (size_t k=0; k < list_length_of(expressions[expr2Length]); ++k) {
                        const expression *expr2 = expressions[expr2Length] + k;

                        expression *newExpr = expressions[newExprLength] + list_length_of(expressions[newExprLength]);
                        if (!expression_combine(newExpr, expr1, expr2, op))
                            continue;

                        if (expression_validate(newExpr)) {
                            print_solution(newExpr, newExprLength);
                            #if CACHE_SOLUTIONS == 0
                            continue;
                            #endif
                        }

                        if (newExprLength != MAX_LENGTH_SEARCHED && hashtable_insert_if_higher(&cache, newExpr->values, op->precedence))
                            list_length_increment(expressions[newExprLength]);
                    }
                }
            }
        }

        printf("Stored %zu expressions\n", list_length_of(expressions[newExprLength]));
    }

    for (size_t i=1; i < MAX_EXPRESSION_LENGTH; ++i)
        list_destroy(expressions[i]);

    hashtable_destroy(cache);
}
