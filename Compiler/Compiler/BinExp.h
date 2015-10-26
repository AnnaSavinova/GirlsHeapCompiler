#pragma once
#include "Grammar.h"
#include "common.h"
class CBinExp : public IExp {
public:
    CBinExp( IExp*, IExp*, std::string );
    ~CBinExp();

private:
    IExp* expression1;
    IExp* expression2;
    std::string operation;
};

