#include "FormalList.h"

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
