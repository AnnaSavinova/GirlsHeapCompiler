#include "FormalList.h"

CFormalList::CFormalList( IVarDecl* _decl )
{
    list.push_back( _decl );
}

CFormalList::CFormalList( std::vector<IVarDecl*>& _list )
{
	list = _list;
}

CFormalList::~CFormalList()
{
}

const std::vector<IVarDecl*>& CFormalList::List() const
{
	return list;
}
