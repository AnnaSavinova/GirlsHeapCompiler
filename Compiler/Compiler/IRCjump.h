#pragma once
#include "common.h"
#include "IRLabel.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( EBinOp relop, IIRExp* left, IIRExp* right, CIRLabel* ifTrue, CIRLabel* ifFalse );
    ~CIRCjump();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const EBinOp relop;
    const IIRExp* left;
    const IIRExp* right;
    const CIRLabel* ifTrue;
    const CIRLabel* ifFalse;
};

