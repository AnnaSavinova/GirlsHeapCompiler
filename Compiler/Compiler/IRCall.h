#pragma once
#include "common.h"

class CIRCall : public IIRExp {
public:
    CIRCall( CSymbol* _func, CIRExpList* args );
    ~CIRCall();

private:
    CSymbol* func;
    CIRExpList* args;
};

