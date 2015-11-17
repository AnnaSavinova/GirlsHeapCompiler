#pragma once
#include "common.h"

class IIRSubtreeWrapper {
public:
    virtual ~IIRSubtreeWrapper() {}

    virtual const IIRExp* ToExp() const = 0; // ��� Expr
    virtual const IIRStm* ToStm() const = 0; // ��� Stm
    virtual const IIRStm* ToConditional( const CLabel* ifTrue, const CLabel* ifFalse ) const = 0; // ��� if/jump

};

