#include "VarDecl.h"

CVarDecl::CVarDecl( IType* _type, std::string _id )
{
	assert( _type != nullptr );
	assert( !_id.empty() );
	type = _type;
	id = _id;
}

CVarDecl::~CVarDecl()
{
	if( type != nullptr ) {
		delete type;
	}
}

//void CVarDecl::Accept( IVisitor* visitor ) const
//{
//	visitor->Visit( this );
//}

