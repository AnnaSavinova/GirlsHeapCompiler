#pragma once
#include "common.h"

class CIRSeq : public IIRStm {
public:
    CIRSeq( IIRStm* left, IIRStm* right );
    CIRSeq( std::list<IIRStm*> list );
    ~CIRSeq();

private:
    IIRStm* left;
    IIRStm* right;
};

