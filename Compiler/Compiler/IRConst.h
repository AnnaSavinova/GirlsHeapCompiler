#pragma once
#include "common.h"

class CIRConst : public IIRExp {
public:
    CIRConst( const int value );
    ~CIRConst();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
    const int value;
};

