#include "Type.h"

CType::CType( const std::string _type )
{
	type = _type;
}

CType::~CType()
{
}

const std::string CType::Type() const
{
	return type;
}