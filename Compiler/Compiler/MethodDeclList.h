#pragma once
#include "common.h"
class CMethodDeclList : public IMethodDeclList
{
public:
    CMethodDeclList( IMethodDecl* _methodDecl );
	CMethodDeclList( const std::vector<IMethodDecl*>& _methodDeclList );

	~CMethodDeclList();
	void Accept( IVisitor* ) const;

	const std::vector<IMethodDecl*> MethodDeclList() const;

private:
	std::vector<IMethodDecl*> methodDeclList;
};