#pragma once
#include "common.h"

class CIRESeq : public IIRExp
{
public:
    CIRESeq( const IIRStm* _stm, const IIRExp* _exp ) : stm( _stm ), exp( _exp ) {};
    const CIRExpList* Kids() const;
    const IIRExp* Build( const CIRExpList* ) const;
    ~CIRESeq();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRStm* stm;
    const IIRExp* exp;
};

