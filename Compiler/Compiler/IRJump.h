#pragma once
#include "common.h"

class CLabel;

class CIRJump : public IIRStm {
public:
    CIRJump( CLabel* _label );
    ~CIRJump();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }
	const CLabel* label;
};

