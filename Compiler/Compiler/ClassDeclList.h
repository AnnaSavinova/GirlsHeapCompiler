#pragma once
#include "common.h"
class CClassDeclList : public IClassDeclList, public CCoord
{
public:
	CClassDeclList( const std::vector<IClassDecl*>& _classDecl, int _line );

    CClassDeclList( IClassDecl* _classDecl, int _line );
	~CClassDeclList();

	const std::vector<IClassDecl*>& ClassDeclList() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
	std::vector<IClassDecl*> classDeclList;
};