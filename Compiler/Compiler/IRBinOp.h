#pragma once
#include "common.h"

class CIRBinOp : public IIRExp
{
public:
    CIRBinOp( EBinOp _operation, const IIRExp* _left, const IIRExp* _right );
    const CIRExpList* Kids() const;
    const IIRExp* Build( const CIRExpList* ) const;
    ~CIRBinOp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const EBinOp operation;
    const IIRExp* left;
    const IIRExp* right;
};

