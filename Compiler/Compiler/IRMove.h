#pragma once
#include "IRStm.h"

class CIRMove :
    public IIRStm {
public:
    CIRMove( IIRExp dst, IIRExp src );
    ~CIRMove();
};

