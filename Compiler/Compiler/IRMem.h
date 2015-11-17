#pragma once
#include "common.h"

class CIRMem : public IIRExp {
public:
  CIRMem(IIRExp* _expression);
  ~CIRMem();

private:
  IIRExp* expression;
};

