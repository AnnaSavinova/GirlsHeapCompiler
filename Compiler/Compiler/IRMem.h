#pragma once
#include "common.h"

class CIRMem : public IIRExp
{
public:
    CIRMem( const IIRExp* _expression );
    const CIRExpList* Kids() const;
    const IIRExp* Build( const CIRExpList* ) const;
    ~CIRMem();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRExp* exp;
};

