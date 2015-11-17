#pragma once
#include "IIRExp.h"

class CIRExp :
    public IIRExp {
public:
    CIRExp( IIRExp exp );
    ~CIRExp();
};

