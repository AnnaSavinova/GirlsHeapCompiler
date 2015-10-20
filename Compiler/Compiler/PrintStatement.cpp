#include "PrintStatement.h"

CPrintStatement::CPrintStatement( IExp* _expression) : expression(_expression)
{
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
