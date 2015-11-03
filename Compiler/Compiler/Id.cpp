#include "Id.h"

CId::CId( std::string s, int _line ) :  id(s)
{
	line = _line;
}


CId::~CId()
{}

std::string CId::Id() const
{
    return id;
}
