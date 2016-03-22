#pragma once
#include "IIRSubtreeWrapper.h"

class CIRStmConverter : public IIRSubtreeWrapper {
public:
    ~CIRStmConverter();

    CIRStmConverter( IIRStm* _stm );
    IIRExp* ToExp() const;
    IIRStm* ToStm() const;
    IIRStm* ToConditional( CLabel* t, CLabel* f ) const;

private:
    IIRStm* stm;
};

