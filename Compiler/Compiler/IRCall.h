#pragma once
#include "common.h"

class CIRCall : public IIRExp {
public:
    CIRCall( IIRExp* _func/*, IRExpList* args*/ );
    ~CIRCall();

private:
    IIRExp* func;
    // IRExpList* args;
};

