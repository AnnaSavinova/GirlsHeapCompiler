#include "ExpList.h"

CExpList::CExpList( IExp* exp )
{
    expressions.push_back( exp );
}

CExpList::CExpList( const std::vector<IExp*>& v ) : expressions(v)
{}


CExpList::~CExpList()
{}

const std::vector<IExp*>& CExpList::Expressions() const
{
	return expressions;
}
