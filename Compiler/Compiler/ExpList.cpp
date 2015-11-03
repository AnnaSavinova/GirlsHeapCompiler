#include "ExpList.h"

CExpList::CExpList( IExp* exp, int _line )
{
	line = _line;
	expressions.push_back( exp );
}

CExpList::CExpList( const std::vector<IExp*>& v, int _line) : expressions( v )
{
	line = _line;
}


CExpList::~CExpList()
{}

const std::vector<IExp*>& CExpList::Expressions() const
{
	return expressions;
}
