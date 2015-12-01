#pragma once
#include "common.h"

class CIRMem : public IIRExp {
public:
  CIRMem( const IIRExp* _expression );
  ~CIRMem();

private:
  const IIRExp* expression;
};

