#pragma once
#include "IIRSubtreeWrapper.h"

class CConditionalWrapper : public IIRSubtreeWrapper {
public:
    CConditionalWrapper( const IIRExp* _exp ) : exp( _exp ) {}
    const IIRExp* ToExp() const;
    const IIRStm* ToStm() const;
    const IIRStm* ToConditional( const CLabel* t, const CLabel* f ) const;
private:
    const IIRExp* exp;

    const IIRStm* binopToConditional( const CIRBinOp* binop, const CLabel* t, const CLabel* f ) const;
    const IIRStm* andBinopToConditional( const CIRBinOp* binop, const CLabel* t, const CLabel* f ) const;
};
