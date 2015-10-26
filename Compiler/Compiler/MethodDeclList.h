#pragma once
#include "common.h"
class CMethodDeclList : public IMethodDeclList
{
public:
	CMethodDeclList( std::vector<IMethodDecl*> &_methodDeclList );
	~CMethodDeclList();
	void Accept( IVisitor* ) const;

	const std::vector<IMethodDecl*>* MethodDeclList() const;

private:
	std::vector<IMethodDecl*> methodDeclList;
};