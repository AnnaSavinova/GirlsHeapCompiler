#include "FormalList.h"

�FormalList::�FormalList( IType * _type, std::string _id, IFormalRestList * _formalRestList )
{
	assert( _type != nullptr );
	assert( !_id.empty() );
	assert( _formalRestList != nullptr );
	type = _type;
	id = _id;
	formalRestList = _formalRestList;
}

�FormalList::~�FormalList()
{
	if( type != nullptr ) {
		delete type;
	}
	if( formalRestList != nullptr ) {
		delete formalRestList;
	}
}
