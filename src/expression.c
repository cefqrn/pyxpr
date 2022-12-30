#include "parameters.h"
#include "expression.h"
#include "macros.h"

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

bool expression_eq(expression newExpr, expression baseExpr) {
    return newExpr.precedence > baseExpr.precedence
        ? false
        : memcmp(newExpr.values, baseExpr.values, sizeof newExpr.values) ? false : true;
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

    op.func(&newExpr, &expr);

    return newExpr;
}

// Combine two expressions with a binary operator
expression combine(expression expr1, expression expr2, operator_binary op) {
    expression newExpr = {
        .precedence = op.precedence,
        .isValid = true
    };
    snprintf(newExpr.text, MAX_EXPRESSION_LENGTH, op.format, expr1.text, expr2.text);

    op.func(&newExpr, &expr1, &expr2);

    return newExpr;
}


#define unaryFunc(name, operation) void name (expression *x, expression *a) { for (size_t i=0; i < VALUE_COUNT; ++i) x->values[i] = operation a->values[i]; }
unaryFunc(paren,   )
unaryFunc(negate, -)
unaryFunc(invert, ~)

#define binaryFunc(name, operation) void name (expression *x, expression *a, expression *b) { for (size_t i=0; i < VALUE_COUNT; ++i) x->values[i] = a->values[i] operation b->values[i]; }
binaryFunc(mul,  *)
binaryFunc(add,  +)
binaryFunc(sub,  -)
binaryFunc(band, &)
binaryFunc(xor,  ^)
binaryFunc(bor,  |)

binaryFunc(lt, < )
binaryFunc(le, <=)
binaryFunc(gt, > )
binaryFunc(ge, >=)
binaryFunc(ne, !=)
binaryFunc(eq, ==)

void exponentiate(expression *x, expression *a, expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i)
        x->values[i] = pow(a->values[i], b->values[i]);
}

void fdiv(expression *x, expression *a, expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (!b->values[i] || (a->values[i] == INT_MIN && b->values[i] == -1)) {
            x->isValid = false;
            return;
        }
        x->values[i] = a->values[i] / b->values[i];
    }
}

void mod (expression *x, expression *a, expression *b) {
    for (size_t i=0; i < VALUE_COUNT; ++i) {
        if (!b->values[i] || (a->values[i] == INT_MIN && b->values[i] == -1)) {
            x->isValid = false;
            return;
        }
        x->values[i] = ((a->values[i] % b->values[i]) + b->values[i]) % b->values[i];
    }
}


// Unary operators

operator_unary paren_operator = {
    .format = "(%s)",
    .func = paren,
    .length = 2,
    .precedence = 15
};

operator_unary invert_operator = {
    .format = "~%s",
    .func = invert,
    .length = 1,
    .precedence = 11
};

operator_unary negate_operator = {
    .format = "-%s",
    .func = negate,
    .length = 1,
    .precedence = 11
};


// Binary operators

operator_binary exponentiation_operator = {
    .format = "%s**%s",
    .func = exponentiate,
    .length = 2,
    .precedence = 12
};

operator_binary mul_operator = {
    .format = "%s*%s",
    .func = mul,
    .length = 1,
    .precedence = 10,
};

operator_binary fdiv_operator = {
    .format = "%s//%s",
    .func = fdiv,
    .length = 2,
    .precedence = 10,
    .hasDivision = true
};

operator_binary mod_operator = {
    .format = "%s%%%s",
    .func = mod,
    .length = 1,
    .precedence = 10,
    .hasDivision = true
};

operator_binary add_operator = {
    .format = "%s+%s",
    .func = add,
    .length = 1,
    .precedence = 9
};

operator_binary sub_operator = {
    .format = "%s-%s",
    .func = sub,
    .length = 1,
    .precedence = 9
};

operator_binary band_operator = {
    .format = "%s&%s",
    .func = band,
    .length = 1,
    .precedence = 7
};

operator_binary xor_operator = {
    .format = "%s^%s",
    .func = xor,
    .length = 1,
    .precedence = 6
};

operator_binary bor_operator = {
    .format = "%s|%s",
    .func = bor,
    .length = 1,
    .precedence = 5
};

operator_binary lt_operator = {
    .format = "%s<%s",
    .func = lt,
    .length = 1,
    .precedence = 4
};

operator_binary le_operator = {
    .format = "%s<=%s",
    .func = le,
    .length = 2,
    .precedence = 4
};

operator_binary gt_operator = {
    .format = "%s>%s",
    .func = gt,
    .length = 1,
    .precedence = 4
};

operator_binary ge_operator = {
    .format = "%s>=%s",
    .func = ge,
    .length = 2,
    .precedence = 4
};

operator_binary ne_operator = {
    .format = "%s!=%s",
    .func = ne,
    .length = 2,
    .precedence = 4
};

operator_binary eq_operator = {
    .format = "%s==%s",
    .func = eq,
    .length = 2,
    .precedence = 4
};
