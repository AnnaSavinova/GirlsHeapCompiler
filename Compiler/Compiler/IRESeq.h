#pragma once
#include "common.h"

class CIRESeq : public IIRExp {
public:
  CIRESeq(IIRStm* _stm, IIRExp* _exp);
  ~CIRESeq();

private:
  IIRStm* statement;
  IIRExp* expression;
};

