#include "FormalRest.h"

CFormalRest::~CFormalRest()
{
	if( type != nullptr ) {
		delete type;
	}
}

CFormalRest::CFormalRest( IType * _type, std::string _id )
{
    assert( _type != nullptr );
    assert( !_id.empty() );
    type = _type;
    id = _id;
}
