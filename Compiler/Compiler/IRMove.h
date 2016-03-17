#pragma once
#include "common.h"

class CIRMove : public IIRStm {
public:
    CIRMove( const IIRExp* dst, const IIRExp* src );
    ~CIRMove();

    const IIRExp* Dst() const;
    const IIRExp* Src() const;
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

private:
    const IIRExp* dst;
    const IIRExp* src;
};

