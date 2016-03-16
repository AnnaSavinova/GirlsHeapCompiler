#pragma once
#include "common.h"
#include "Temp.h"

class CIRLabel : public IIRStm {
public:
    CIRLabel( CLabel* label );
    ~CIRLabel();

private:
    CLabel* label;
};

