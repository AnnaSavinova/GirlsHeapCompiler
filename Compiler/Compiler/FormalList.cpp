#include "FormalList.h"

ÑFormalList::ÑFormalList( IType * _type, std::vector<std::string>& _idList )
{
	assert( _type != nullptr );
	assert( !_idList.empty() );
	type = _type;
	idList = _idList;
}

ÑFormalList::~ÑFormalList()
{
	if( type != nullptr ) {
		delete type;
	}
}

const IType * ÑFormalList::Type() const
{
	return type;
}

const std::vector<std::string>& ÑFormalList::IdList() const
{
	return idList;
}
