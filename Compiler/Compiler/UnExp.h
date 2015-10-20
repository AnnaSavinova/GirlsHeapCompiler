#pragma once
#include "common.h"

class CUnExp :
    public IExp {
public:
    CUnExp( IExp*, std::string );
    ~CUnExp();

private:
    IExp* expression;
    std::string operation;
};

