#include "common.h"
#include "WhileStatement.h"

CWhileStatement::CWhileStatement( IExp * _expression, IStatement * _statement ) : expression(_expression), statement(_statement)
{
    assert( _expression );
    assert( _statement );
}

CWhileStatement::~CWhileStatement()
{
    delete expression;
    delete statement;
}

const IExp * CWhileStatement::Expression() const
{
    return expression;
}

const IStatement * CWhileStatement::Statement() const
{
    return statement;
}
