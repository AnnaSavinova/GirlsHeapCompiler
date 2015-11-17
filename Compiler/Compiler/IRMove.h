#pragma once
#include "IIRStm.h"

class CIRMove :
    public IIRStm {
public:
    CIRMove( IIRExp dst, IIRExp src );
    ~CIRMove();
};

