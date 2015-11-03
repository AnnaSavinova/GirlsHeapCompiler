#include "FormalList.h"

CFormalList::CFormalList( CFormalListElement* _elem, int _line )
{
	line = _line;
	list.push_back( _elem );
}

CFormalList::CFormalList( std::vector<CFormalListElement*>& _list, int _line )
{
	line = _line;
	list = _list;
}

CFormalList::~CFormalList()
{
}

const std::vector<CFormalListElement*>& CFormalList::List() const
{
	return list;
}
