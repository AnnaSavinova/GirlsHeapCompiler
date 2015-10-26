#include "LengthExp.h"



CLengthExp::CLengthExp( IExp* exp) : expression(exp)
{
    assert( exp != nullptr );
}


CLengthExp::~CLengthExp()
{
    delete expression;
}

const IExp* CLengthExp::Expression() const
{
	return expression;
}
