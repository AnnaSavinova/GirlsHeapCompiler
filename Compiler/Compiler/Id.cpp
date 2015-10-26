#include "Id.h"

CId::CId( std::string s ) : id(s)
{}


CId::~CId()
{}

std::string CId::Id() const
{
    return id;
}
