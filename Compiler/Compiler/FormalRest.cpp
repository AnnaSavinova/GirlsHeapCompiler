#include "FormalRest.h"

ÑFormalRest::ÑFormalRest( IType * _type, std::string _id )
{
	assert( _type != nullptr );
	assert( !_id.empty() );
	type = _type;
	id = _id;
}

ÑFormalRest::~ÑFormalRest()
{
	if( type != nullptr ) {
		delete type;
	}
}
