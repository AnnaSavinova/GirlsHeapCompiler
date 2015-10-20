#include "common.h"
#include "IfStatement.h"

CIfStatement::CIfStatement( IExp * _expression, IStatement* _thenStatement, IStatement * _elseStatement) : expression(_expression), thenStatement(_thenStatement), elseStatement(_elseStatement)
{
    assert( _expression );
    assert( _thenStatement );
    assert( _elseStatement );
}

CIfStatement::~CIfStatement()
{
    delete expression;
    delete thenStatement;
    delete elseStatement;
}

const IExp * CIfStatement::Expression() const
{
    return expression;
}

const IStatement * CIfStatement::ThenStatement() const
{
    return thenStatement;
}

const IStatement * CIfStatement::ElseStatement() const
{
    return elseStatement;
}
