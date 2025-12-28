#ifndef __MEXPR_ENUMS__
#define __MEXPR_ENUMS__

typedef enum {

    MATH_CPP_INT ,
    MATH_CPP_DOUBLE,
    MATH_CPP_VARIABLE,
    MATH_CPP_IPV4,

    MATH_CPP_DTYPE_MAX
    
} mexprcpp_dtypes_t;

typedef enum {
    PARSER_EOL = (int) MATH_CPP_DTYPE_MAX + 1,
} EXTRA_ENUMS;

#endif
