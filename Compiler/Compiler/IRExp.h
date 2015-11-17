#pragma once
#include "common.h"

class CIRExp : public IIRStm {
public:
    CIRExp( const IIRExp* exp );
    ~CIRExp();

private:
    const IIRExp* exp;
};

