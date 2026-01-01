#ifndef __DTYPE__
#define __DTYPE__

#include <bits/stdc++.h>
#include "MexprcppEnums.h"
#include "MexprTree.h"

class Dtype : public MexprNode {
    protected:
        Dtype();

    public:
        mexprcpp_dtypes_t did; // dtype id
        virtual ~Dtype();
};

class Dtype_INT: public Dtype{
    public:
        struct {
            int int_val;
        } dtype;

        Dtype_INT();
        Dtype_INT(int val);
        ~Dtype_INT();
};

class Dtype_STRING: public Dtype{
    public:
        struct {
            std::string string_val;
        } dtype;

        Dtype_STRING();
        Dtype_STRING(std::string val);
        ~Dtype_STRING();
}; 

#endif