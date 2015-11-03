#pragma once
#include "common.h"
class CNewInt :
    public IExp, public CCoord
{
public:
    CNewInt( IExp*, int _line );
    ~CNewInt();

	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
};

