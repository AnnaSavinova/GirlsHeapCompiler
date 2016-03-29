#pragma once
#include "common.h"
#include "Temp.h"

class CIRTemp : public IIRExp
{
public:
    CIRTemp( const CTemp* _temp );
    const CIRExpList* Kids() const;
    const IIRExp* Build( const CIRExpList* ) const;
    ~CIRTemp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const CTemp* temp;
};

