#include "LengthExp.h"



CLengthExp::CLengthExp( IExp* exp, int _line ) : expression(exp)
{
	line = _line;
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
