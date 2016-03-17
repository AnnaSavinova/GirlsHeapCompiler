#pragma once
#include "common.h"

class CIRLabel;

class CIRJump : public IIRStm {
public:
    CIRJump( CIRLabel* _label );
    ~CIRJump();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
	const CIRLabel* label;
};

