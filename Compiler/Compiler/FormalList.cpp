#include "FormalList.h"

�FormalList::�FormalList( IVarDecl* _decl )
{
    list.push_back( _decl );
}

�FormalList::�FormalList( std::vector<IVarDecl*>& _list )
{
	list = _list;
}

�FormalList::~�FormalList()
{
}

const std::vector<IVarDecl*>& �FormalList::List() const
{
	return list;
}
