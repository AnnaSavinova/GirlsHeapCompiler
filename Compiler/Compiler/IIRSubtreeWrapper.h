#pragma once
#include "common.h"
#include "Temp.h"
#include "IIRExp.h"
#include "IIRStm.h"

class IIRSubtreeWrapper {
public:
    virtual ~IIRSubtreeWrapper() {}

    virtual const IIRExp* ToExp() const = 0; // ��� Expr
    virtual const IIRStm* ToStm() const = 0; // ��� Stm
    virtual const IIRStm* ToConditional( const CLabel* ifTrue, const CLabel* ifFalse ) const = 0; // ��� if/jump

};
