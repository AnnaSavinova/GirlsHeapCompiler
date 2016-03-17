#pragma once
#include "common.h"

class CIRExp : public IIRStm {
public:
    CIRExp( const IIRExp* exp );
    ~CIRExp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
    const IIRExp* exp;
};

