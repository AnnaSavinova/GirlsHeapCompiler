#pragma once
#include "IIRSubtreeWrapper.h"

class CIRStmConverter : public IIRSubtreeWrapper {
public:
    ~CIRStmConverter();

    CIRStmConverter( const IIRStm* _stm );
    const IIRExp* ToExp() const;
    const IIRStm* ToStm() const;
    const IIRStm* ToConditional( const CLabel* t, const CLabel* f ) const;

private:
    const IIRStm* stm;
};

