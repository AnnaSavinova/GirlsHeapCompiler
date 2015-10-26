#pragma once
#include "common.h"
class CClassDeclList : public IClassDeclList
{
public:
	CClassDeclList( std::vector<IClassDecl*> &_classDeclList );

    CClassDeclList( IClassDecl* _classDecl );
	~CClassDeclList();

	const std::vector<IClassDecl*>* ClassDeclList() const;

private:
	std::vector<IClassDecl*> classDeclList;
};