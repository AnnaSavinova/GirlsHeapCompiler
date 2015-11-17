#pragma once
#include "common.h"

class CIRSeq : public IIRStm {
public:
    CIRSeq( IIRStm* left, IIRStm* right );
    ~CIRSeq();

private:
    IIRStm* left;
    IIRStm* right;
};

