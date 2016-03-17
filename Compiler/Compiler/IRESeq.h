#pragma once
#include "common.h"

class CIRESeq : public IIRExp
{
public:
    CIRESeq( IIRStm* _stm, IIRExp* _exp );
    ~CIRESeq();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRStm* stm;
    const IIRExp* exp;
};

