#pragma once
#include "common.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( ECondOp relop, IIRExp* left, IIRExp* right, CLabel* ifTrue, CLabel* ifFalse );
    ~CIRCjump();

private:
    ECondOp relop;
    IIRExp* left;
    IIRExp* right;
    CLabel* ifTrue;
    CLabel* ifFalse;
};

