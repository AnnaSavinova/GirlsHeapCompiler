#include "Constructor.h"

CConstructor::CConstructor( std::string _id, int _line ) : id( symbolStorage.Get(_id) ) 
{
	line = _line;
}


CConstructor::~CConstructor()
{}

CSymbol* CConstructor::Id() const
{
    return id;
}
