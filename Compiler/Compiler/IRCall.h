#pragma once
#include "common.h"

class CIRCall : public IIRExp {
public:
    CIRCall( const IIRExp* _func, const CIRExpList* args );
    const CIRExpList* Kids() const;
    const IIRExp* Build( const CIRExpList* ) const;
    ~CIRCall();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRExp* func;
    const CIRExpList* args;
};

