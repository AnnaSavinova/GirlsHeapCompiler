#include "ClassDeclList.h"

CClassDeclList::CClassDeclList( std::vector<IClassDecl*>& _classDeclList )
{
	for( size_t i = 0; i < _classDeclList.size(); i++ ) {
		assert( _classDeclList[i] );
	}
	classDeclList = _classDeclList;
}

CClassDeclList::CClassDeclList( IClassDecl* _classDecl )
{    
    assert( _classDecl );
    classDeclList.push_back( _classDecl );
}

CClassDeclList::~CClassDeclList()
{
	for( size_t i = 0; i < classDeclList.size(); i++ ) {
		if( classDeclList[i] ) {
			delete classDeclList[i];
		}
	}
}

const std::vector<IClassDecl*>* CClassDeclList::ClassDeclList() const
{
	return &classDeclList;
}


