#pragma once
#include "common.h"

class CClassDecl : public IClassDecl
{
public:
	CClassDecl( CSymbol*, CSymbol*, IVarDeclList*,  IMethodDecls* );
	~CClassDecl();
	void Accept( IVisitor* ) const;

private:
	CSymbol* id, parentId; // parentId can be null
	IVarDeclList* varDecls;
	IMethodDecls* methodDecls;
};