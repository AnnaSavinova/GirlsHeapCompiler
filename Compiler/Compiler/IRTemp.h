#pragma once
#include "common.h"

class CIRTemp : public IIRExp {
public:
  CIRTemp(CTemp* _temp);
  ~CIRTemp();

private:
  CTemp* temp;
};

