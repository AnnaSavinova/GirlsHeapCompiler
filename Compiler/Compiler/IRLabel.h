#pragma once
#include "common.h"

class CIRLabel : public IIRStm {
public:
    CIRLabel( CLabel* label );
    ~CIRLabel();

private:
    CLabel* label;
};

