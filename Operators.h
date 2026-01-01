#ifndef __OPERATORS__
#define __OPERATORS__

#include<bits/stdc++.h>
#include "MexprcppEnums.h"
#include "MexprTree.h"
using namespace std;

class Operator : public MexprNode {
    protected:
        Operator();
        virtual ~Operator();

    public:
        int opid;
        string name;
        bool is_unary;
};

class OperatorPlus : public Operator {
    public:
        OperatorPlus();
        ~OperatorPlus();
};

#endif