#include "PrintStatement.h"

CPrintStatement::CPrintStatement( IExp* _expression, int _line ) :  expression(_expression)
{
	line = _line;
    assert( _expression != nullptr );
}


CPrintStatement::~CPrintStatement()
{
    delete expression;
}

const IExp * CPrintStatement::Expression() const
{
    return expression;
}
