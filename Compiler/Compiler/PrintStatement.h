#pragma once
#include "common.h"
class CPrintStatement : public IStatement, public CCoord
{
public:
    CPrintStatement( IExp*, int _line );
    ~CPrintStatement();

    const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
};

