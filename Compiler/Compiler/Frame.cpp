#include "Frame.h"

CFrame::CFrame( const CSymbol * name, int formalsCount )
{}

int CFrame::FormalsCount() const
{
    return formals.size();
}

const IAccess * CFrame::Formal( size_t index ) const
{
    return nullptr;
}

const IAccess * CFrame::Local( const CSymbol * var ) const
{
    auto access = locals.find( var );
    if( access != locals.end() ) {
        return access->second;
    } else {
        return nullptr;
    }
}

const CTemp* CFrame::FP() const
{
    return fp;
}

int CFrame::WordSize()
{
    return wordSize;
}

CLabel::CLabel() : name( std::to_string( nextUniqueId++ ) )
{}

CLabel::CLabel( const std::string& s ) : name( s )
{}

const std::string & CLabel::Name() const
{
    return name;
}

CTemp::CTemp() : name( std::to_string( nextUniqueId++ ) )
{}

CTemp::CTemp( const CSymbol * symbol ) : name( symbol->String() )
{}

CTemp::~CTemp()
{}
