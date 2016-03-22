#pragma once
#include "common.h"
#include "Temp.h"
#include "IIRExp.h"
#include "IIRStm.h"

class IIRSubtreeWrapper {
public:
    virtual ~IIRSubtreeWrapper() {}

    virtual const IIRExp* ToExp() const = 0; // как Expr
    virtual const IIRStm* ToStm() const = 0; // как Stm
    virtual const IIRStm* ToConditional( const CLabel* ifTrue, const CLabel* ifFalse ) const = 0; // как if/jump

};
