#pragma once
#include "common.h"

class CIRBinOp : public IIRExp
{
public:
    CIRBinOp( EBinOp _operation, IIRExp* _left, IIRExp* _right );
    ~CIRBinOp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const EBinOp operation;
    IIRExp* left;
    IIRExp* right;
};

