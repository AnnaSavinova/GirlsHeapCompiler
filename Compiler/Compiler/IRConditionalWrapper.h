#pragma once
#include "IIRSubtreeWrapper.h"
#include "IRClasses.h"

class CConditionalWrapper : public IIRSubtreeWrapper {
public:
    CConditionalWrapper( IIRExp* _exp ) : exp( _exp ) {}
    IIRExp* ToExp() const;
    IIRStm* ToStm() const;
    IIRStm* ToConditional( CLabel* t, CLabel* f ) const;
private:
    IIRExp* exp;

    IIRStm* binopToConditional( CIRBinOp* binop, CLabel* t, CLabel* f ) const;
    IIRStm* andBinopToConditional( CIRBinOp* binop, CLabel* t, CLabel* f ) const;
};
