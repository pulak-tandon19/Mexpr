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

#endif