#include "ExpList.h"

CExpList::CExpList( const std::vector<IExp*>& v ) : expressions(v)
{}


CExpList::~CExpList()
{}

const std::vector<IExp*>* CExpList::Expressions() const
{
	return &expressions;
}
