#include "NewClass.h"



CNewClass::CNewClass( std::string ID): id(ID)
{}


CNewClass::~CNewClass()
{}

const std::string CNewClass::Id() const
{
	return id;
}
