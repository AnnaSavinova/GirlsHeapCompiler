#include "AssignmentStatement.h"


CAssignmentStatement::CAssignmentStatement( std::string _id, IExp* _expression, int _line ) : id(symbolStorage.Get(_id)), expression(_expression)
{
	line = _line;
    assert( _expression != nullptr );
}


CAssignmentStatement::~CAssignmentStatement()
{
    delete expression;
}

CSymbol* CAssignmentStatement::Id() const
{
	return id;
}

const IExp* CAssignmentStatement::Expression() const
{
	return expression;
}
