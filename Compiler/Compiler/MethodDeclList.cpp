#include "MethodDeclList.h"

CMethodDeclList::CMethodDeclList( IMethodDecl* _methodDecl )
{
    methodDeclList.push_back( _methodDecl );
}

CMethodDeclList::CMethodDeclList( const std::vector<IMethodDecl*>& _methodDeclList )
{
	for( size_t i = 0; i < _methodDeclList.size(); i++ ) {
		assert( _methodDeclList[i] );
	}
	methodDeclList = _methodDeclList;
}

CMethodDeclList::~CMethodDeclList()
{
	for( size_t i = 0; i < methodDeclList.size(); i++ ) {
		if( methodDeclList[i] ) {
			delete methodDeclList[i];
		}
	}
}

const std::vector<IMethodDecl*> CMethodDeclList::MethodDeclList() const
{
	return methodDeclList;
}


