#pragma once
#include "Grammar.h"
#include "common.h"
class CWhileStatement : public IStatement {
public:
    CWhileStatement( IExp*, IStatement* );
    ~CWhileStatement();

    const IExp* Expression() const;
    const IStatement* Statement() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
    IStatement* statement;
};

