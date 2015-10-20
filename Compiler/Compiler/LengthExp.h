#pragma once
#include "common.h"
class CLengthExp :
    public IExp {
public:
    CLengthExp( IExp* );
    ~CLengthExp();

private:
    IExp* expression;
};

