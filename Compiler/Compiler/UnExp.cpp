#include "UnExp.h"



CUnExp::CUnExp( IExp* exp, std::string op ) : expression(exp), operation(op)
{
    assert( exp != nullptr );
}


CUnExp::~CUnExp()
{
	if ( expression != nullptr ) {
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

