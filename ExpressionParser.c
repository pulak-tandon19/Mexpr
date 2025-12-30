#include <stdio.h>
#include "ParserExport.h"
#include "MexprcppEnums.h"

/*

A Grammar to parse mathematical expression !

1. E -> E + T | E - T | T
2. T -> T * F | T / F | F
3. F -> ( E ) | INTEGER | DECIMAL | VAR 

Now remove left recursion from it :

1. E -> E + T | E - T | T
E ->  T E'
E' -> + T E' | - T E' |  $   ( $ represents epsilon)

2. T -> T * F | T / F | F
T -> F T'
T' -> * F T' |   / F T'  |  $

Combining everything, final grammar is : 

1.    E   ->   T E’
2.    E’  ->  + T E' | - T E' |  $
3.    T  ->   F T’
4.    T’ ->   * F T' |   / F T'  |  $
5.    F  ->   ( E ) |  INTEGER | DECIMAL | VAR
6.    Q -> E INEQ E
7.    INEQ ->     MATH_CPP_EQ  |  MATH_CPP_NEQ |  MATH_CPP_LESS_THAN  |   MATH_CPP_LESS_THAN_EQ
*/

parse_rc_t E() ;
parse_rc_t Q() ;
static parse_rc_t E_dash() ;
static parse_rc_t T() ;
static parse_rc_t T_dash() ;
static parse_rc_t F() ;
static parse_rc_t INEQ() ;

parse_rc_t 
E() { 
    parse_init();

    err = T();

    if (err == PARSE_ERR) 
        RETURN_PARSE_ERROR;

    err = E_dash();

    if (err == PARSE_ERR)
        RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

parse_rc_t 
E_dash() {
    parse_init();

    int chkp;
    CHECKPOINT(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_PLUS)
            break;
        
        err = T();
        if (err == PARSE_ERR)
            break;

        err = E_dash();
        if (err == PARSE_ERR)
            break;

        RETURN_PARSE_SUCCESS;

    }while(0);

    RESTORE_CHKP(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_MINUS)
            break;

        err = T();
        if (err == PARSE_ERR)
            break;

        err = E_dash();
        if (err == PARSE_ERR)
            break;

        RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(chkp);

    RETURN_PARSE_SUCCESS;
}

parse_rc_t
T() {
    parse_init();

    err = F();
    if (err == PARSE_ERR)
        RETURN_PARSE_ERROR;

    err = T_dash();
    if (err == PARSE_ERR)
        RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

parse_rc_t
T_dash() {
    parse_init();

    int chkp;
    CHECKPOINT(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_MUL)
            break;

        err = F();
        if (err == PARSE_ERR)
            break;

        err = T_dash();
        if (err == PARSE_ERR)
            break;

        RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_DIV)
            break;

        err = F();
        if (err == PARSE_ERR)
            break;

        err = T_dash();
        if (err == PARSE_ERR)
            break;

        RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(chkp);

    RETURN_PARSE_SUCCESS;
}

parse_rc_t
F() {
    parse_init();

    int chkp;   
    CHECKPOINT(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_BRACKET_START)
            break;

        err = E();
        if (err == PARSE_ERR)
            break;

        token_code = cyylex();
        if (token_code != MATH_CPP_BRACKET_END)
            break;

        RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(chkp);

    do {
        token_code = cyylex();
        if (token_code != MATH_CPP_INT && token_code != MATH_CPP_DOUBLE && token_code != MATH_CPP_VARIABLE)
            break;

        RETURN_PARSE_SUCCESS;
    }while(0);

    RETURN_PARSE_ERROR;
}

parse_rc_t
Q() {
    parse_init();

    err = E();
    if (err == PARSE_ERR)
        RETURN_PARSE_ERROR;

    token_code = cyylex();
    if (token_code == PARSE_ERR) {
        RETURN_PARSE_ERROR;
    }

    err = E();
    if (err == PARSE_ERR)
        RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

parse_rc_t
INEQ() {
    parse_init();

    switch (token_code) {
        case MATH_CPP_EQ:
        case MATH_CPP_NEQ:
        case MATH_CPP_LESS_THAN:
        case MATH_CPP_LESS_THAN_EQ:
        case MATH_CPP_GREATER_THAN:
        case MATH_CPP_GREATER_THAN_EQ:
            // All these cases fall through to the success return
            RETURN_PARSE_SUCCESS;

        default:
            // If the token matches none of the above, it's a parse error
            RETURN_PARSE_ERROR;
    }
}
