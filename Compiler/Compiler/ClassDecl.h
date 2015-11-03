#pragma once
#include "common.h"

class CClassDecl : public IClassDecl, public CCoord
{
public:
	CClassDecl( std::string, std::string, IVarDeclList*,  IMethodDeclList*, int _line );
	~CClassDecl();

	CSymbol* Id() const;
	CSymbol* ParentId() const;
	const IVarDeclList* VarDeclList() const;
	const IMethodDeclList* MethodDeclList() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}


private:
  CSymbol* id;
  CSymbol* parentId; // parentId can be null
	IVarDeclList* varDecls; // can be null
	IMethodDeclList* methodDecls; // can be null
};