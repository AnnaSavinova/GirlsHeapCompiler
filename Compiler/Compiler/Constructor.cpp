#include "Constructor.h"



CConstructor::CConstructor( std::string _id ) : id( _id )
{}


CConstructor::~CConstructor()
{}

std::string CConstructor::Id() const
{
    return id;
}
