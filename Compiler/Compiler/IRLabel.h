#pragma once
#include "common.h"
#include "Temp.h"

class CIRLabel : public IIRStm {
public:
    CIRLabel( CLabel* label );
    ~CIRLabel();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const CLabel* label;
};

