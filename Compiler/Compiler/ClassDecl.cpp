#include "ClassDecl.h"

CClassDecl::CClassDecl( CSymbol* _id, CSymbol* _parentId, IVarDeclList* _varDecls, IMethodDecls* _methodDecls ) :
	id( _id ),
	parentId( _parentId ),
	varDecls( _varDecls ),
	methodDecls( _methodDecls )

{
	assert( _id != nullptr );
	assert( _varDecls != nullptr );
	assert( _methodDecls != nullptr );
}

CClassDecl::~CClassDecl()
{
	if ( id != nullptr ) {
		delete type;
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

