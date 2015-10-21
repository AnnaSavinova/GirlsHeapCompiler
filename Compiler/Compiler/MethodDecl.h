#pragma once
#include "common.h"

class CMethodDecl : public IMethodDecl
{
public:
	CMethodDecl( IType* _type, std::string _id, IFormalList* _formalList,
		IVarDeclList* _varDeclList, IStatementList* _statementList,
		IExp* _exp );
	~CMethodDecl();
	
	const IType* Type() const;
	const std::string Id() const;
	const IFormalList* FormalList() const;
	const IVarDeclList* VarDeclList() const;
	const IStatementList* StatementList() const;
	const IExp* Expression() const;

private:
	IType* type;
	std::string id;
	IFormalList* formalList;
	IVarDeclList* varDeclList;
	IStatementList* statementList;
	IExp* exp;
};