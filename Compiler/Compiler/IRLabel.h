#pragma once
#include "common.h"
#include "Temp.h"

class CIRLabel : public IIRStm {
public:
    CIRLabel( CLabel* label );
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    ~CIRLabel();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const CLabel* label;
};

