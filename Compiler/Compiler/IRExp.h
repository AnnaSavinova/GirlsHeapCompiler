#pragma once
#include "common.h"

class CIRExp : public IIRStm {
public:
    CIRExp( const IIRExp* exp );
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    ~CIRExp();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
    const IIRExp* exp;
};

