#pragma once
#include "common.h"
class CPrintStatement : public IStatement {
public:
    CPrintStatement( IExp* );
    ~CPrintStatement();

    const IExp* Expression() const;
private:
    IExp* expression;
};

