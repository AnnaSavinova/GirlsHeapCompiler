#pragma once
#include "common.h"
class CClassDeclList : public IClassDeclList
{
public:
	CClassDeclList( const std::vector<IClassDecl*>& _classDecl );

    CClassDeclList( IClassDecl* _classDecl );
	~CClassDeclList();

	const std::vector<IClassDecl*>& ClassDeclList() const;

private:
	std::vector<IClassDecl*> classDeclList;
};