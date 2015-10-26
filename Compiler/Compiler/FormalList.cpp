#include "FormalList.h"

�FormalList::�FormalList( IType * _type, std::vector<std::string>& _idList )
{
	assert( _type != nullptr );
	assert( !_idList.empty() );
	type = _type;
	idList = _idList;
}

�FormalList::~�FormalList()
{
	if( type != nullptr ) {
		delete type;
	}
}

const IType * �FormalList::Type() const
{
	return type;
}

const std::vector<std::string>& �FormalList::IdList() const
{
	return idList;
}
