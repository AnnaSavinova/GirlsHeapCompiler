#include "Constructor.h"



CConstructor::CConstructor( std::string _id, int _line ) : id( _id ) 
{
	line = _line;
}


CConstructor::~CConstructor()
{}

std::string CConstructor::Id() const
{
    return id;
}
