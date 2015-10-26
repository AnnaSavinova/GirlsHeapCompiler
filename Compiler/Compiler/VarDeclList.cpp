#include "VarDeclList.h"

CVarDeclList::CVarDeclList( std::vector<IVarDecl*>& _varDeclList )
{
	for( size_t i = 0; i < _varDeclList.size(); i++ ) {
		assert( _varDeclList[i] );
	}
	varDeclList = _varDeclList;
}

CVarDeclList::CVarDeclList( IVarDecl* _varDecl )
{
    varDeclList.push_back( _varDecl );
}

CVarDeclList::~CVarDeclList()
{
	for( size_t i = 0; i < varDeclList.size(); i++ ) {
		if( varDeclList[i] ) {
			delete varDeclList[i];
		}
	}
}

const std::vector<IVarDecl*>& CVarDeclList::VarDeclList() const
{
	return varDeclList;
}

