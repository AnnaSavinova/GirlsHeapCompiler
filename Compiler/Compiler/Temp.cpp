#include "Temp.h"

CLabelList::CLabelList( const CLabel * _head, const CLabelList * _tail ): head(_head), tail(_tail)
{}

const CLabel * CLabelList::GetHead()
{
    return head;
}

const CLabelList * CLabelList::GetTail()
{
    return tail;
}

CTempList::CTempList( const CTemp * _head, const CTempList * _tail ) : head( _head ), tail( _tail )
{}

const CTemp * CTempList::GetHead() const
{
    return head;
}

const CTempList * CTempList::GetTail() const
{
    return tail;
}

CLabel::CLabel() : name( "label_" + std::to_string( nextUniqueId++ ) )
{}

CLabel::CLabel( const std::string& s ) : name( s )
{}

const std::string & CLabel::Name() const
{
    return name;
}

CTemp::CTemp() : name( "temp_" + std::to_string( nextUniqueId++ ) )
{}

CTemp::CTemp( const CSymbol * symbol ) : name( symbol->String() )
{}

CTemp::~CTemp()
{}
