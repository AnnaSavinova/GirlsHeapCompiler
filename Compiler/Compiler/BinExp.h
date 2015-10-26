#pragma once
#include "common.h"
class CBinExp : public IExp {
public:
    CBinExp( IExp*, IExp*, std::string );
    ~CBinExp();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}


private:
    IExp* expression1;
    IExp* expression2;
    std::string operation;
};

