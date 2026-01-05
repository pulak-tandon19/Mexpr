#include<bits/stdc++.h>
#include<stdio.h>
#include "MexprTree.h"
#include "Dtype.h"
#include "Operators.h"
#include "MexprcppEnums.h"
#include "ParserExport.h"

extern parse_rc_t E();
extern parse_rc_t Q();
extern parse_rc_t S();

extern lex_data_t **mexpr_convert_infix_to_postfix (
                                 lex_data_t *infix, 
                                 int sizein, 
                                 int *size_out);

static void
postfix_array_free(lex_data_t **lex_data_array, int size) {
   
    for (int i = 0; i < size; i++) {

        if (lex_data_array[i])
        {
            if (lex_data_array[i]->token_val) free(lex_data_array[i]->token_val);
            free(lex_data_array[i]);
        }
    }

    free(lex_data_array);
}


int main() {

    parse_rc_t err;
    int token_code;

    while (1) {
        printf("Input:- ");

        fgets(lex_buffer, sizeof(lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer(lex_buffer);
        parser_stack_reset();

        err = Q();

        if (err == PARSE_ERR) {
            err = E();

            if (err == PARSE_ERR) {
                printf("Error: Unable to parse expression\n");
                continue;
            }
        }

        token_code = cyylex();

        if (token_code != PARSER_EOL) {
            printf ("Error : Parsing Error, Entire Input String is not a Valid Expression.\n");
            continue;
        }

        int size_out = 0;

        lex_data_t **postfix = mexpr_convert_infix_to_postfix(undo_stack.data, undo_stack.top + 1, &size_out);
        
        MexprTree *tree = new MexprTree(postfix, size_out);

        if (!tree) {
            printf ("Error : Failed to build Expression Tree\n");
            continue;
        }

        if (!tree->validate (tree->root)) {
            printf ("Error : Expression Tree failed Loose-Validation Test\n");
            tree->destroy();
            continue;
        }

        Dtype *res = tree->evaluate (tree->root);

        /* Done with the expression Tree*/
        tree->destroy();

        if (!res ) {
            printf ("Error : Expression Tree Could not be evaluated\n");
            continue;
        }

        printf ("Result : ");

        switch (res->did) {

            case MATH_CPP_INT:
                printf ("%d\n",  reinterpret_cast <Dtype_INT *> (res)->dtype.int_val);
                break;
            case MATH_CPP_DOUBLE:
                printf ("%lf\n",  reinterpret_cast <Dtype_DOUBLE *> (res)->dtype.d_val);
                break;
            case MATH_CPP_STRING:
                printf ("%s\n",  reinterpret_cast <Dtype_STRING *> (res)->dtype.str_val.c_str());
                break;
            case MATH_CPP_BOOL:
            {
                Dtype_BOOL *dtype_b = reinterpret_cast <Dtype_BOOL *>(res);
                dtype_b->dtype.b_val == true ? printf ("True") : printf("False");
                printf("\n");
            }
            break;
            default:
                assert(0);
        }

        delete res;
        
    }

    return 0;
}

