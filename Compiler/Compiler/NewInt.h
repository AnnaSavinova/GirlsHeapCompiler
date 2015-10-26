#pragma once
#include "common.h"
class CNewInt :
    public IExp {
public:
    CNewInt( IExp* );
    ~CNewInt();

	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
};

