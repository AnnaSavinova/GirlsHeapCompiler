#pragma once
#include "common.h"

class CIRCall : public IIRExp {
public:
    CIRCall( IIRExp* _func, CIRExpList* args );
    ~CIRCall();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRExp* func;
    const CIRExpList* args;
};

