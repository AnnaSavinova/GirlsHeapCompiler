#include "ClassDecl.h"

CClassDecl::CClassDecl( CSymbol* _id, CSymbol* _parentId, IVarDeclList* _varDecls, IMethodDeclList* _methodDecls ) :
	id( _id ),
	parentId( _parentId ),
	varDecls( _varDecls ),
	methodDecls( _methodDecls )
{
	assert( _id != nullptr );
}

CClassDecl::~CClassDecl()
{
	if ( id != nullptr ) {
		delete id;
	}

	if ( parentId != nullptr ) {
		delete parentId;
	}

	if ( varDecls != nullptr ) {
		delete varDecls;
	}

	if ( methodDecls != nullptr ) {
		delete methodDecls;
	}
}

//void CClassDecl::Accept( IVisitor* visitor ) const
//{
//	visitor->Visit( this );
//}

