#pragma once
#include "common.h"
#include "Temp.h"

class CIRName : public IIRExp {
public:
    CIRName( CLabel* _label );
    ~CIRName();

private:
    CLabel* label;
};

