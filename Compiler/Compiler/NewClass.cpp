#include "NewClass.h"



CNewClass::CNewClass( std::string ID, int _line ) :  id(ID)
{
	line = _line;
}


CNewClass::~CNewClass()
{}

const std::string CNewClass::Id() const
{
	return id;
}
