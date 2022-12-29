#include "operator.h"

#include <stdbool.h>
#include <math.h>

int paren (int x) { return x;  }
int negate(int x) { return -x; }
int invert(int x) { return ~x; }

int mul (int a, int b) { return a * b; }
int fdiv(int a, int b) { return a / b; }
int mod (int a, int b) { return ((a % b) + b) % b; }
int add (int a, int b) { return a + b; }
int sub (int a, int b) { return a - b; }
int band(int a, int b) { return a & b; }
int xor (int a, int b) { return a ^ b; }
int bor (int a, int b) { return a | b; }

int lt  (int a, int b) { return a <  b; }
int le  (int a, int b) { return a <= b; }
int gt  (int a, int b) { return a >  b; }
int ge  (int a, int b) { return a >= b; }
int ne  (int a, int b) { return a != b; }
int eq  (int a, int b) { return a == b; }

int exponentiate(int a, int b) {
    return pow(a, b);
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
