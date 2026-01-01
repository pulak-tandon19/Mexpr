#include "Operators.h"

Operator:: Operator() {
    opid = MATH_CPP_OPR_INVALID;
    name = "";
    is_unary = false;
}

Operator:: ~Operator() {
}

OperatorPlus:: OperatorPlus() {
    opid = MATH_CPP_PLUS;
    name = "+";
    is_unary = false;
}

OperatorPlus:: ~OperatorPlus() {
}
