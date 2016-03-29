#pragma once
#include "common.h"

class CIRSeq : public IIRStm {
public:
    CIRSeq( const IIRStm* _left, const IIRStm* _right ) : left( _left ), right( _right ) {};
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    CIRSeq( std::list<IIRStm*> list );
    ~CIRSeq();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    const IIRStm* left;
    const IIRStm* right;
};

