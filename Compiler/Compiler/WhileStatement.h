#pragma once
#include "common.h"

class CWhileStatement : public IStatement {
public:
    CWhileStatement( IExp*, IStatement* );
    ~CWhileStatement();

    const IExp* Expression() const;
    const IStatement* Statement() const;

private:
    IExp* expression;
    IStatement* statement;
};

