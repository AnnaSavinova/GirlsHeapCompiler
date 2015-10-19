#pragma once
#include "common.h"

class CIfStatement : IStatement {
public:
    CIfStatement( IExp*, IStatement*, IStatement* );
    ~CIfStatement();

    const IExp* Expression() const;
    const IStatement* ThenStatement() const;
    const IStatement* ElseStatement() const;

private:
    IExp* expression;
    IStatement* thenStatement;
    IStatement* elseStatement;
};