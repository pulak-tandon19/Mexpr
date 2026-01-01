#ifndef __MEXPR_TREE__
#define __MEXPR_TREE__

#include<bits/stdc++.h>
#include "MexprcppEnums.h"

class MexprNode {
    protected:
        MexprNode();

    public:
        virtual ~MexprNode();
};

typedef struct lex_data_ lex_data_t;

class MexprTree {

    public:
        MexprNode *root;
        MexprNode *lst_head;
        MexprTree(lex_data_t **postfix_lex_dat_array, int size);
};

#endif