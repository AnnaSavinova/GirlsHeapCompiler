#pragma once
#include "common.h"

class CClassDecl : public IClassDecl
{
public:
	CClassDecl( CSymbol*, CSymbol*, IVarDeclList*,  IMethodDeclList* );
	~CClassDecl();
	void Accept( IVisitor* ) const;

private:
	CSymbol* id, parentId; // parentId can be null
	IVarDeclList* varDecls; // can be null
	IMethodDeclList* methodDecls; // can be null
};