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

