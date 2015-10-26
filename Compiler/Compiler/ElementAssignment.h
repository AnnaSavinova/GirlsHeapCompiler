#pragma once
#include "common.h"

class CElementAssignment : public IStatement {
public:
    CElementAssignment( std::string, IExp*, IExp* );
    ~CElementAssignment();

private:
    std::string id;
    IExp* exp1;
    IExp* exp2;
};

