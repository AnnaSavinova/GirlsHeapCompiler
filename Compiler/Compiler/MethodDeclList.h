#pragma once
#include "common.h"
class CMethodDeclList : public IMethodDeclList, public CCoord
{
public:
    CMethodDeclList( IMethodDecl* _methodDecl, int _line );
	CMethodDeclList( const std::vector<IMethodDecl*>& _methodDeclList, int _line );

	~CMethodDeclList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IMethodDecl*> MethodDeclList() const;

private:
	std::vector<IMethodDecl*> methodDeclList;
};