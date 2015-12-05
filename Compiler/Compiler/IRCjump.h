#pragma once
#include "common.h"
#include "IRLabel.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( EBinOp relop, IIRExp* left, IIRExp* right, CIRLabel* ifTrue, CIRLabel* ifFalse );
    ~CIRCjump();

private:
    EBinOp relop;
    IIRExp* left;
    IIRExp* right;
    CIRLabel* ifTrue;
    CIRLabel* ifFalse;
};

