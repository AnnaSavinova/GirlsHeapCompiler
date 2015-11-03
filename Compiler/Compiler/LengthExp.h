#pragma once
#include "common.h"
class CLengthExp : public IExp, public CCoord
{
public:
    CLengthExp( IExp*, int _line );
    ~CLengthExp();

	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
};

