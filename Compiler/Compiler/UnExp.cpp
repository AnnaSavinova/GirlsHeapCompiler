#include "UnExp.h"



CUnExp::CUnExp( IExp* exp, std::string op, int _line ) : expression( exp ), operation( op )
{
	line = _line;
	assert( exp != nullptr );
}


CUnExp::~CUnExp()
{
	if( expression != nullptr ) {
		delete expression;
	}
}

const IExp* CUnExp::Expression() const
{
	return expression;
}

const std::string CUnExp::Operation() const
{
	return operation;
}

