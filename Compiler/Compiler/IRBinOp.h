#pragma once
#include "common.h"

class CIRBinOp : public IIRExp {
public:
  CIRBinOp(EBinOp _operation, IIRExp* _left, IIRExp* _right);
  ~CIRBinOp();

private:
  EBinOp operation;
  IIRExp* left, *right;
};

