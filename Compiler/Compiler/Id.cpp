#include "Id.h"

CId::CId( std::string s, int _line ) :  id( symbolStorage.Get( s ) )
{
	line = _line;
}


CId::~CId()
{}

CSymbol* CId::Id() const
{
    return id;
}
