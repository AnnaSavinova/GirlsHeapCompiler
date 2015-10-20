#pragma once
#include "common.h"
class CAssignmentStatement : public IStatement {
public:
    CAssignmentStatement( std::string, IExp* );
    ~CAssignmentStatement();

private:
    std::string id;
    IExp* expression;
};

