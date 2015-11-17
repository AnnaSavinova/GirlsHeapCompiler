#pragma once
#include "common.h"

class CIRJump : public IIRStm {
public:
    CIRJump( IIRExp* exp, std::vector< CTemp* > targets );
    ~CIRJump();

private:
    IIRExp* exp;
    std::vector< CTemp* > targets;
};

