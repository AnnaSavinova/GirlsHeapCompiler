#pragma once
#include "common.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( int relop, IIRExp* left, IIRExp* right, CLabel* ifTrue, CLabel* ifFalse );
    ~CIRCjump();

private:
    int relop;
    IIRExp* left;
    IIRExp* right;
    CLabel* ifTrue;
    CLabel* ifFalse;
};

