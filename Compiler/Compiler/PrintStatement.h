#pragma once
#include "common.h"
class CPrintStatement : public IStatement {
public:
    CPrintStatement( IExp* );
    ~CPrintStatement();

    const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
};

