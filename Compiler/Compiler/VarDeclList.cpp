#include "VarDeclList.h"

CVarDeclList::CVarDeclList( std::vector<IStatement*>& _varDeclList )
{
	for( size_t i = 0; i < _varDeclList.size(); i++ ) {
		assert( _varDeclList[i] );
	}
	varDeclList = _varDeclList;
}

CVarDeclList::~CVarDeclList()
{
	for( size_t i = 0; i < varDeclList.size(); i++ ) {
		if( varDeclList[i] ) {
			delete varDeclList[i];
		}
	}
}


