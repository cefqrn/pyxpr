#include "operator.h"

#include <stdbool.h>
#include <math.h>

int paren (int x) { return x;  }
int negate(int x) { return -x; }
int invert(int x) { return ~x; }

int mul (int a, int b) { return a * b; }
int fdiv(int a, int b) { return a / b; }
int mod (int a, int b) { return a % b; }
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
    // does not support negative exponents (negative exponents require floats)
    return pow(a, b);
}

// completely wrong if a or b aren't 1 digit
int append_digit(int a, int b) {
    return a*10 + b;
}


// unary operators

struct operator_unary paren_operator = {
    .format = "(%s)",
    .func = paren,
    .length = 2,
    .precedence = 15
};

struct operator_unary invert_operator = {
    .format = "~%s",
    .func = invert,
    .length = 1,
    .precedence = 11
};

struct operator_unary negate_operator = {
    .format = "-%s",
    .func = negate,
    .length = 1,
    .precedence = 11
};


// binary operators

struct operator_binary append_digit_operator = {
    .format = "%s%s",
    .func = append_digit,
    .length = 0,
    .precedence = CONSTANT_PRECEDENCE
};

struct operator_binary exponentiation_operator = {
    .format = "%s**%s",
    .func = exponentiate,
    .length = 2,
    .precedence = 12
};

struct operator_binary mul_operator = {
    .format = "%s*%s",
    .func = mul,
    .length = 1,
    .precedence = 10,
};

struct operator_binary fdiv_operator = {
    .format = "%s//%s",
    .func = fdiv,
    .length = 2,
    .precedence = 10,
    .requiresTruthySecondExpression = true
};

struct operator_binary mod_operator = {
    .format = "%s%%%s",
    .func = mod,
    .length = 1,
    .precedence = 10,
    .requiresTruthySecondExpression = true
};

struct operator_binary add_operator = {
    .format = "%s+%s",
    .func = add,
    .length = 1,
    .precedence = 9
};

struct operator_binary sub_operator = {
    .format = "%s-%s",
    .func = sub,
    .length = 1,
    .precedence = 9
};

struct operator_binary band_operator = {
    .format = "%s&%s",
    .func = band,
    .length = 1,
    .precedence = 7
};

struct operator_binary xor_operator = {
    .format = "%s^%s",
    .func = xor,
    .length = 1,
    .precedence = 6
};

struct operator_binary bor_operator = {
    .format = "%s|%s",
    .func = bor,
    .length = 1,
    .precedence = 5
};

struct operator_binary lt_operator = {
    .format = "%s<%s",
    .func = lt,
    .length = 1,
    .precedence = 4
};

struct operator_binary le_operator = {
    .format = "%s<=%s",
    .func = le,
    .length = 2,
    .precedence = 4
};

struct operator_binary gt_operator = {
    .format = "%s>%s",
    .func = gt,
    .length = 1,
    .precedence = 4
};

struct operator_binary ge_operator = {
    .format = "%s>=%s",
    .func = ge,
    .length = 2,
    .precedence = 4
};

struct operator_binary ne_operator = {
    .format = "%s!=%s",
    .func = ne,
    .length = 2,
    .precedence = 4
};

struct operator_binary eq_operator = {
    .format = "%s==%s",
    .func = eq,
    .length = 2,
    .precedence = 4
};


// array of unary operators in reverse order of precedence
struct operator_unary *UNARY_OPERATORS[] = {
    &negate_operator,
    &invert_operator,
    &paren_operator,
};

// array of binary operators in reverse order of precedence
struct operator_binary *BINARY_OPERATORS[] = {
    &lt_operator,
    &le_operator,
    &gt_operator,
    &ge_operator,
    &ne_operator,
    &eq_operator,
    &bor_operator,
    &xor_operator,
    &band_operator,
    &sub_operator,
    &add_operator,
    &fdiv_operator,
    &mod_operator,
    &mul_operator,
    &exponentiation_operator,
    // &append_digit_operator,
};
