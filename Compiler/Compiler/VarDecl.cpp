#include "VarDecl.h"

CVarDecl::CVarDecl( IType* _type, std::string _id, int _line )
{
	line = _line;
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

const IType* CVarDecl::Type() const
{
	return type;
}

const std::string CVarDecl::Id() const
{
	return id;
}

//void CVarDecl::Accept( IVisitor* visitor ) const
//{
//	visitor->Visit( this );
//}

