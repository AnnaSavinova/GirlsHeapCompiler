#pragma once
#include "Grammar.h"
#include "common.h"
class CIfStatement : public IStatement, public CCoord
{
public:
    CIfStatement( IExp*, IStatement*, IStatement*, int _line );
    ~CIfStatement();

    const IExp* Expression() const;
    const IStatement* ThenStatement() const;
    const IStatement* ElseStatement() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
    IStatement* thenStatement;
    IStatement* elseStatement;
};