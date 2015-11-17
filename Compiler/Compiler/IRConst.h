#pragma once
#include "common.h"

class CIRConst : public IIRExp {
public:
    CIRConst( int value );
    ~CIRConst();

private:
    int value;
};

