#pragma once
#include "common.h"

class CIRName : public IIRExp {
public:
  CIRName(CLabel* _label);
  ~CIRName();

private:
  CLabel* label;
};

