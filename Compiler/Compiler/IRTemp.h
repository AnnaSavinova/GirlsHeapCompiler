#pragma once
#include "common.h"
#include "Temp.h"

class CIRTemp : public IIRExp
{
public:
    CIRTemp( const CTemp* _temp );
    ~CIRTemp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const CTemp* temp;
};

