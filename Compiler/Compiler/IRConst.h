#pragma once
#include "common.h"

class CIRConst : public IIRExp {
public:
    CIRConst( const int value );
    ~CIRConst();

private:
    int value;
};

