#pragma once
#include "Grammar.h"
#include "common.h"
class CIfStatement : public IStatement {
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