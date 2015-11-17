#pragma once
#include "IIRSubtreeWrapper.h"

class CIRExpConverter : public IIRSubtreeWrapper {
public:
    ~CIRExpConverter();

    CIRExpConverter( const IIRExp* _exp );
    const IIRExp* ToExp() const;
    const IIRStm* ToStm() const;
    const IIRStm* ToConditional( const CLabel* t, const CLabel* f ) const;

private:
    const IIRExp* exp;
};

