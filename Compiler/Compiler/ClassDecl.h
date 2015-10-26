#pragma once
#include "common.h"

class CClassDecl : public IClassDecl
{
public:
	CClassDecl( std::string, std::string, IVarDeclList*,  IMethodDeclList* );
	~CClassDecl();

	const std::string Id() const;
	const std::string ParentId() const;
	const IVarDeclList* VarDeclList() const;
	const IMethodDeclList* MethodDeclList() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}


private:
	std::string id, parentId; // parentId can be null
	IVarDeclList* varDecls; // can be null
	IMethodDeclList* methodDecls; // can be null
};