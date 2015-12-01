#pragma once
#include "common.h"

class CIRMove : public IIRStm {
public:
    CIRMove( const IIRExp* dst, const IIRExp* src );
    ~CIRMove();

private:
    const IIRExp* dst;
    const IIRExp* src;
};

