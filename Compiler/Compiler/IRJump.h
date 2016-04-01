#pragma once
#include "common.h"

class CLabel;

class CIRJump : public IIRStm {
public:
    CIRJump( const CLabel* _label );
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    ~CIRJump();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
	const CLabel* label;
};

