#include "Frame.h"

CFrame::CFrame( const CSymbol* name, int formalsCount, const IIRStm* root )
{}

int CFrame::FormalsCount() const
{
    return formals.size();
}

const IAccess * CFrame::Formal( const CSymbol* var ) const
{
	auto access = formals.find( var );
	if( access != formals.end() ) {
		return access->second;
	} else {
		return nullptr;
	}
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

const IAccess * CFrame::Temporary( const CSymbol * var ) const
{
	auto access = temporaries.find( var );
	if( access != temporaries.end() ) {
		return access->second;
	} else {
		return nullptr;
	}
}

const IAccess* CFrame::FindVar( const CSymbol * var ) const
{
	const IAccess* formal = Formal( var );
	if( formal != nullptr ) {
		return formal;
	} else {
		return Local( var );
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
