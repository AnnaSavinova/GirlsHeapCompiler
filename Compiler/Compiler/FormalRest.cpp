#include "FormalRest.h"

FormalRest::FormalRest( IType * _type, std::string _id )
{
	assert( _type != nullptr );
	assert( !_id.empty() );
	type = _type;
	id = _id;
}

FormalRest::~FormalRest()
{
	if( type != nullptr ) {
		delete type;
	}
}
