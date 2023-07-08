#include "operator.h"

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define UNARY_FUNC(name, operation) \
    bool name(int *restrict x, const int *a) { \
        for (size_t i=0; i < VALUE_COUNT; ++i) \
            x[i] = operation a[i]; \
        return true; \
    }

UNARY_FUNC(paren_func,  );
UNARY_FUNC(  neg_func, -);
UNARY_FUNC(  inv_func, ~);

#define BINARY_FUNC(name, operation) \
    bool name(int *restrict x, const int *a, const int *b) { \
        for (size_t i=0; i < VALUE_COUNT; ++i) \
            x[i] = a[i] operation b[i]; \
        return true; \
    }

BINARY_FUNC(combine_func, * 10 +);

BINARY_FUNC( mul_func, *);
BINARY_FUNC( add_func, +);
BINARY_FUNC( sub_func, -);
BINARY_FUNC(band_func, &);
BINARY_FUNC( xor_func, ^);
BINARY_FUNC( bor_func, |);

BINARY_FUNC(lt_func, < );
BINARY_FUNC(le_func, <=);
BINARY_FUNC(gt_func, > );
BINARY_FUNC(ge_func, >=);
BINARY_FUNC(ne_func, !=);
BINARY_FUNC(eq_func, ==);

bool pow_func(int *restrict x, const int *a, const int *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (a[i] == 0 && b[i] < 0)  // python doesn't allow raising 0 to a negative power
            return false;

        x[i] = pow(a[i], b[i]);
    }

    return true;
}

bool fdiv_func(int *restrict x, const int *a, const int *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (b[i] == 0 || (a[i] == INT_MIN && b[i] == -1))
            return false;

        // C's int div truncates instead of flooring
        x[i] = floor((double)a[i] / b[i]);
    }

    return true;
}

bool mod_func(int *restrict x, const int *a, const int *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (b[i] == 0 || (a[i] == INT_MIN && b[i] == -1))
            return false;

        // C's mod gives the remainder
        x[i] = ((a[i] % b[i]) + b[i]) % b[i];
    }

    return true;
}

#define CHAINED_FUNC(name, operation) \
    bool name(int *restrict x, const int *a, const int *b, const int *c) { \
        for (size_t i=0; i < VALUE_COUNT; ++i) \
            x[i] = a[i] && (c[i] operation b[i]); \
        return true; \
    }

CHAINED_FUNC(lt_chained_func, < );
CHAINED_FUNC(le_chained_func, <=);
CHAINED_FUNC(gt_chained_func, > );
CHAINED_FUNC(ge_chained_func, >=);
CHAINED_FUNC(ne_chained_func, !=);
CHAINED_FUNC(eq_chained_func, ==);

const operator OPERATOR_ATOM[OPERATOR_ATOM_COUNT] = {
    [INT_LITERAL] = { .format = "%s", .precedence = INT_LITERAL_PRECEDENCE },
    [VARIABLE   ] = { .format =  "x", .precedence = 16 },
};

const operator OPERATOR_UNARY[OPERATOR_UNARY_COUNT] = {
    [PAREN_OPERATOR] = { .format = "(%s)", .precedence = 15, .length = 2, .unaryFunc = paren_func },
    [INV_OPERATOR  ] = { .format =  "~%s", .precedence = 11, .length = 1, .unaryFunc =   inv_func },
    [NEG_OPERATOR  ] = { .format =  "-%s", .precedence = 11, .length = 1, .unaryFunc =   neg_func },
};

const operator OPERATOR_BINARY[OPERATOR_BINARY_COUNT] = {
    #if CONCAT_NUMBERS == 1
    [CONCAT_NUMBER] = { .format =   "%s%s", .precedence = INT_LITERAL_PRECEDENCE, .length = 0, .binaryFunc = combine_func },
    #endif
    [POW_OPERATOR ] = { .format = "%s**%s", .precedence = 12, .length = 2, .binaryFunc =  pow_func },
    [MUL_OPERATOR ] = { .format =  "%s*%s", .precedence = 10, .length = 1, .binaryFunc =  mul_func },
    [FDIV_OPERATOR] = { .format = "%s//%s", .precedence = 10, .length = 2, .binaryFunc = fdiv_func },
    [MOD_OPERATOR ] = { .format = "%s%%%s", .precedence = 10, .length = 1, .binaryFunc =  mod_func },
    [ADD_OPERATOR ] = { .format =  "%s+%s", .precedence =  9, .length = 1, .binaryFunc =  add_func },
    [SUB_OPERATOR ] = { .format =  "%s-%s", .precedence =  9, .length = 1, .binaryFunc =  sub_func },
    [BAND_OPERATOR] = { .format =  "%s&%s", .precedence =  7, .length = 1, .binaryFunc = band_func },
    [XOR_OPERATOR ] = { .format =  "%s^%s", .precedence =  6, .length = 1, .binaryFunc =  xor_func },
    [BOR_OPERATOR ] = { .format =  "%s|%s", .precedence =  5, .length = 1, .binaryFunc =  bor_func },
    [LT_OPERATOR  ] = { .format =  "%s<%s", .precedence =  COMPARISON_PRECEDENCE, .length = 1, .binaryFunc = lt_func, .chainedFunc = lt_chained_func },
    [LE_OPERATOR  ] = { .format = "%s<=%s", .precedence =  COMPARISON_PRECEDENCE, .length = 2, .binaryFunc = le_func, .chainedFunc = le_chained_func },
    [GT_OPERATOR  ] = { .format =  "%s>%s", .precedence =  COMPARISON_PRECEDENCE, .length = 1, .binaryFunc = gt_func, .chainedFunc = gt_chained_func },
    [GE_OPERATOR  ] = { .format = "%s>=%s", .precedence =  COMPARISON_PRECEDENCE, .length = 2, .binaryFunc = ge_func, .chainedFunc = ge_chained_func },
    [NE_OPERATOR  ] = { .format = "%s!=%s", .precedence =  COMPARISON_PRECEDENCE, .length = 2, .binaryFunc = ne_func, .chainedFunc = ne_chained_func },
    [EQ_OPERATOR  ] = { .format = "%s==%s", .precedence =  COMPARISON_PRECEDENCE, .length = 2, .binaryFunc = eq_func, .chainedFunc = eq_chained_func },
};
