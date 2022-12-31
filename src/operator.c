#include "expression.h"
#include "operator.h"

#include <limits.h>
#include <math.h>

#define UNARY_FUNC(name, operation) \
    void name(expression *x, const expression *a) { \
        for (size_t i=0; i < VALUE_COUNT; ++i) \
            x->values[i] = operation a->values[i]; \
    }

UNARY_FUNC(paren_func,  );
UNARY_FUNC(  neg_func, -);
UNARY_FUNC(  inv_func, ~);

#define BINARY_FUNC(name, operation) \
    void name(expression *x, const expression *a, const expression *b) { \
        for (size_t i=0; i < VALUE_COUNT; ++i) \
            x->values[i] = a->values[i] operation b->values[i]; \
    }

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

void pow_func(expression *x, const expression *a, const expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i)
        x->values[i] = pow(a->values[i], b->values[i]);
}

void fdiv_func(expression *x, const expression *a, const expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (!b->values[i] || (a->values[i] == INT_MIN && b->values[i] == -1)) {
            x->isValid = false;
            return;
        }
        x->values[i] = a->values[i] / b->values[i];
    }
}

void mod_func(expression *x, const expression *a, const expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (!b->values[i] || (a->values[i] == INT_MIN && b->values[i] == -1)) {
            x->isValid = false;
            return;
        }
        x->values[i] = ((a->values[i] % b->values[i]) + b->values[i]) % b->values[i];
    }
}

const operator OPERATOR_ATOM[OPERATOR_ATOM_COUNT] = {
    [VARIABLE   ] = { .format =  "x", .precedence = 17 },
    [INT_LITERAL] = { .format = "%s", .precedence = 16 },
};

const operator OPERATOR_UNARY[OPERATOR_UNARY_COUNT] = {
    [PAREN_OPERATOR] = { .format = "(%s)", .precedence = 15, .length = 2, .unaryFunc = &paren_func },
    [INV_OPERATOR  ] = { .format =  "~%s", .precedence = 11, .length = 1, .unaryFunc =   &inv_func },
    [NEG_OPERATOR  ] = { .format =  "-%s", .precedence = 11, .length = 1, .unaryFunc =   &neg_func },
};

const operator OPERATOR_BINARY[OPERATOR_BINARY_COUNT] = {
    [POW_OPERATOR ] = { .format = "%s**%s", .precedence = 12, .length = 2, .binaryFunc =  &pow_func },
    [MUL_OPERATOR ] = { .format =  "%s*%s", .precedence = 10, .length = 1, .binaryFunc =  &mul_func },
    [FDIV_OPERATOR] = { .format = "%s//%s", .precedence = 10, .length = 2, .binaryFunc = &fdiv_func },
    [MOD_OPERATOR ] = { .format = "%s%%%s", .precedence = 10, .length = 1, .binaryFunc =  &mod_func },
    [ADD_OPERATOR ] = { .format =  "%s+%s", .precedence =  9, .length = 1, .binaryFunc =  &add_func },
    [SUB_OPERATOR ] = { .format =  "%s-%s", .precedence =  9, .length = 1, .binaryFunc =  &sub_func },
    [BAND_OPERATOR] = { .format =  "%s&%s", .precedence =  7, .length = 1, .binaryFunc = &band_func },
    [XOR_OPERATOR ] = { .format =  "%s^%s", .precedence =  6, .length = 1, .binaryFunc =  &xor_func },
    [BOR_OPERATOR ] = { .format =  "%s|%s", .precedence =  5, .length = 1, .binaryFunc =  &bor_func },
    [LT_OPERATOR  ] = { .format =  "%s<%s", .precedence =  4, .length = 1, .binaryFunc =   &lt_func },
    [LE_OPERATOR  ] = { .format = "%s<=%s", .precedence =  4, .length = 2, .binaryFunc =   &le_func },
    [GT_OPERATOR  ] = { .format =  "%s>%s", .precedence =  4, .length = 1, .binaryFunc =   &gt_func },
    [GE_OPERATOR  ] = { .format = "%s>=%s", .precedence =  4, .length = 2, .binaryFunc =   &ge_func },
    [NE_OPERATOR  ] = { .format = "%s!=%s", .precedence =  4, .length = 2, .binaryFunc =   &ne_func },
    [EQ_OPERATOR  ] = { .format = "%s==%s", .precedence =  4, .length = 2, .binaryFunc =   &eq_func },
};
