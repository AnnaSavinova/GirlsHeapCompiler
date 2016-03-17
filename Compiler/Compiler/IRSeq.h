#pragma once
#include "common.h"

class CIRSeq : public IIRStm {
public:
    CIRSeq( IIRStm* left, IIRStm* right );
    CIRSeq( std::list<IIRStm*> list );
    ~CIRSeq();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRStm* left;
    const IIRStm* right;
};

