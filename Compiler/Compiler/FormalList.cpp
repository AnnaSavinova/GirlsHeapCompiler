#include "FormalList.h"

ÑFormalList::ÑFormalList( IVarDecl* _decl )
{
    list.push_back( _decl );
}

ÑFormalList::ÑFormalList( std::vector<IVarDecl*>& _list )
{
	list = _list;
}

ÑFormalList::~ÑFormalList()
{
}

const std::vector<IVarDecl*>& ÑFormalList::List() const
{
	return list;
}
