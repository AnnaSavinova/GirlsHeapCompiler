#pragma once
#include "common.h"
class CNewInt :
    public IExp {
public:
    CNewInt( IExp* );
    ~CNewInt();

private:
    IExp* expression;
};

