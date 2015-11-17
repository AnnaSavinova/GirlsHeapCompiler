#pragma once
#include "common.h"

class CIRMove : public IIRStm {
public:
    CIRMove( IIRExp* dst, IIRExp* src );
    ~CIRMove();

private:
    IIRExp* dst;
    IIRExp* src;
};

