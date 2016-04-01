#pragma once
#include "IIRSubtreeWrapper.h"
#include "IRClasses.h"

class CConditionalWrapper : public IIRSubtreeWrapper {
public:
    CConditionalWrapper( const IIRExp* _exp ) : exp( _exp ) {}
    IIRExp* ToExp() const;
    IIRStm* ToStm() const;
    IIRStm* ToConditional( CLabel* t, CLabel* f ) const;
private:
    const IIRExp* exp;

    IIRStm* binopToConditional( const CIRBinOp* binop, CLabel* t, CLabel* f ) const;
    IIRStm* andBinopToConditional( const CIRBinOp* binop, CLabel* t, CLabel* f ) const;
};
