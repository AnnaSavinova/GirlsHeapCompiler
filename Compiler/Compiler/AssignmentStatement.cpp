#include "AssignmentStatement.h"


CAssignmentStatement::CAssignmentStatement( std::string _id, IExp* _expression ) : id(_id), expression(_expression)
{
    assert( _expression != nullptr );
}


CAssignmentStatement::~CAssignmentStatement()
{
    delete expression;
}
