#pragma once
#include "IIRSubtreeWrapper.h"

class CIRExpConverter : public IIRSubtreeWrapper {
public:
    ~CIRExpConverter();

    CIRExpConverter( IIRExp* _exp );
    IIRExp* ToExp() const;
    IIRStm* ToStm() const;
    IIRStm* ToConditional( CLabel* t, CLabel* f ) const;

private:
    IIRExp* exp;
};

