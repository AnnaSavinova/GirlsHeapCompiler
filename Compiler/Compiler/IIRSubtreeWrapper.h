#pragma once
#include "common.h"
#include "Temp.h"
#include "IIRExp.h"
#include "IIRStm.h"

class IIRSubtreeWrapper {
public:
    virtual ~IIRSubtreeWrapper() {}

    virtual IIRExp* ToExp() const = 0; // ��� Expr
    virtual IIRStm* ToStm() const = 0; // ��� Stm
    virtual IIRStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const = 0; // ��� if/jump

};
