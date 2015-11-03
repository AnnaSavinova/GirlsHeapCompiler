#include "AssignmentStatement.h"


CAssignmentStatement::CAssignmentStatement( std::string _id, IExp* _expression, int _line ) : id(_id), expression(_expression)
{
	line = _line;
    assert( _expression != nullptr );
}


CAssignmentStatement::~CAssignmentStatement()
{
    delete expression;
}

const std::string CAssignmentStatement::Id() const
{
	return id;
}

const IExp* CAssignmentStatement::Expression() const
{
	return expression;
}
