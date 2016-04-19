#pragma once
#include "common.h"
#include "IRLabel.h"

class CIRCjump : public IIRStm {
public:
    CIRCjump( const EBinOp relop, const IIRExp* left, const IIRExp* right, const CLabel* ifTrue, const CLabel* ifFalse );
    ~CIRCjump();
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    static EBinOp BuildNotCondition(const EBinOp relop) {
      switch (relop) {
      case EQ:  return NE;
      case NE:  return EQ;
      case LESS:  return GT;
      case GT:  return LESS;
      default:
        assert(false);
      }
    }

    const EBinOp relop;
    const IIRExp* left;
    const IIRExp* right;
    const CLabel* ifTrue;
    const CLabel* ifFalse;
};

