#include "Grammar.h"
#include "WhileStatement.h"

CWhileStatement::CWhileStatement( IExp * _expression, IStatement * _statement, int _line ) : expression( _expression ), statement( _statement )
{
	line = _line;
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
