#pragma once
#include "common.h"
class CBinExp : public IExp {
public:
    CBinExp( IExp*, IExp*, std::string );
    ~CBinExp();

	const IExp* Expression1() const;
	const IExp* Expression2() const;
	const std::string Operation() const;

	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    IExp* expression1;
    IExp* expression2;
    std::string operation;
};

