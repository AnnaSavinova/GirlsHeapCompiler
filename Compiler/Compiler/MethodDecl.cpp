#include "MethodDecl.h"

CMethodDecl::CMethodDecl( IType* _type, std::string _name, IFormalList* _formalList,
	IVarDeclList* _varDeclList, IStatementList* _statementList,
	IExp* _result, int _line )
{
	line = _line;
	assert( _type != nullptr );
	assert( !_name.empty() );
	type = _type;
	name = symbolStorage.Get(_name);
	formalList = _formalList;
	varDeclList = _varDeclList;
	statementList = _statementList;
	result = _result;
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
	if( result != nullptr ) {
		delete result;
	}
}

const IType* CMethodDecl::Type() const
{
	return type;
}

CSymbol* CMethodDecl::Name() const
{
	return name;
}

const IFormalList* CMethodDecl::FormalList() const
{
	return formalList;
}

const IVarDeclList* CMethodDecl::VarDeclList() const
{
	return varDeclList;
}

const IStatementList* CMethodDecl::StatementList() const
{
	return statementList;
}

const IExp* CMethodDecl::Result() const
{
	return result;
}

