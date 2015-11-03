#include "NewClass.h"



CNewClass::CNewClass( std::string _id, int _line ) :  id( symbolStorage.Get( _id) )
{
	line = _line;
}


CNewClass::~CNewClass()
{}

CSymbol* CNewClass::Id() const
{
	return id;
}
