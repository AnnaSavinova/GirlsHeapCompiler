#pragma once
#include "common.h"
#include "Temp.h"

class CIRTemp : public IIRExp {
public:
    CIRTemp( const CTemp* _temp );
    ~CIRTemp();

private:
    const CTemp* temp;
};

