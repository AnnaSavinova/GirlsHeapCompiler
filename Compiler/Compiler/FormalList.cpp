#include "FormalList.h"

CFormalList::CFormalList( CFormalListElement* _elem )
{
    list.push_back( _elem );
}

CFormalList::CFormalList( std::vector<CFormalListElement*>& _list )
{
	list = _list;
}

CFormalList::~CFormalList()
{
}

const std::vector<CFormalListElement*>& CFormalList::List() const
{
	return list;
}
