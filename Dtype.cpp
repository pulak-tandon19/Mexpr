#include "Dtype.h"

Dtype:: Dtype() {
    did = MATH_CPP_DTYPE_INVALID;
}

Dtype:: ~Dtype() {
}

Dtype_INT:: Dtype_INT() {
    did = MATH_CPP_INT;
}

Dtype_INT:: Dtype_INT(int val) {
    did = MATH_CPP_INT;
    dtype.int_val = val;
}

Dtype_INT:: ~Dtype_INT() {
}

Dtype_STRING:: Dtype_STRING() {
    did = MATH_CPP_STRING;
}

Dtype_STRING:: Dtype_STRING(std::string val) {
    did = MATH_CPP_STRING;
    dtype.string_val = val;
}

Dtype_STRING:: ~Dtype_STRING() {
}
    