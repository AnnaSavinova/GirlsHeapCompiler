#include "ClassDeclList.h"

CClassDeclList::CClassDeclList( const std::vector<IClassDecl*>& _classDecl ) : classDeclList(_classDecl)
{}

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

const std::vector<IClassDecl*>& CClassDeclList::ClassDeclList() const
{
	return classDeclList;
}


