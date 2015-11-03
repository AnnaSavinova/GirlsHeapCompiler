#include "NewInt.h"



CNewInt::CNewInt( IExp* exp, int _line ) :  expression(exp)
{
	line = _line;
    assert( expression != nullptr );
}


CNewInt::~CNewInt()
{
    delete expression;
}

const IExp * CNewInt::Expression() const
{
	return expression;
}
