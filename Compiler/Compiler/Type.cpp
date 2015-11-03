#include "Type.h"

CType::CType( const std::string _type, int _line )
{
	line = _line;
	type = _type;
}

CType::~CType()
{
}

const std::string CType::Type() const
{
	return type;
}