#pragma once
#include "common.h"
#include "Temp.h"

class CIRName : public IIRExp {
public:
    CIRName( CLabel* _label );
    ~CIRName();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const CLabel* label;
};

