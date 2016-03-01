#pragma once
#include "common.h"

class CIRLabel;

class CIRJump : public IIRStm {
public:
    CIRJump( CIRLabel* _label );
    ~CIRJump();

private:
	CIRLabel* label;
};

