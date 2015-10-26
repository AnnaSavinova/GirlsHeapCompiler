#pragma once
#include "Grammar.h"
#include "common.h"
class CUnExp :
    public IExp {
public:
    CUnExp( IExp*, std::string );
    ~CUnExp();

	const IExp* Expression() const;
	const std::string Operation() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression;
    std::string operation;
};

