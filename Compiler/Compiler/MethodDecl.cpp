#include "MethodDecl.h"

CMethodDecl::CMethodDecl( IType* _type, std::string _id, IFormalList* _formalList,
	IVarDeclList* _varDeclList, IStatementList* _statementList,
	IExp* _exp )
{
	assert( _type != nullptr );
	assert( !_id.empty() );
	assert( _formalList != nullptr );
	assert( _varDeclList != nullptr );
	assert( _statementList != nullptr );
	assert( _exp != nullptr );
	type = _type;
	id = _id;
	formalList = _formalList;
	varDeclList = _varDeclList;
	statementList = _statementList;
	exp = _exp;
}

CMethodDecl::~CMethodDecl()
{
	if( type != nullptr ) {
		delete type;
	}
	if( formalList != nullptr ) {
		delete formalList;
	}
	if( varDeclList != nullptr ) {
		delete varDeclList;
	}
	if( statementList != nullptr ) {
		delete statementList;
	}
	if( exp != nullptr ) {
		delete exp;
	}
}

