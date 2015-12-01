#pragma once
#include "common.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( EBinOp relop, IIRExp* left, IIRExp* right, CLabel* ifTrue, CLabel* ifFalse );
    ~CIRCjump();

private:
    EBinOp relop;
    IIRExp* left;
    IIRExp* right;
    CLabel* ifTrue;
    CLabel* ifFalse;
};

