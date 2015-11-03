#pragma once
#include "common.h"
class CVarDeclList : public IVarDeclList, public CCoord
{
public:
	CVarDeclList( std::vector<IVarDecl*>& _varDeclList, int _line );
    CVarDeclList( IVarDecl* _varDecl, int _line );

	~CVarDeclList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IVarDecl*>& VarDeclList() const;

private:
	std::vector<IVarDecl*> varDeclList;
};