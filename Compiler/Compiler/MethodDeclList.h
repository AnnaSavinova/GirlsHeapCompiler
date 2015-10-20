#pragma once
#include "common.h"

class CVarDeclList : public IVarDeclList
{
public:
	CVarDeclList( std::vector<IVarDecl*> &_varDeclList );
	~CVarDeclList();
	void Accept( IVisitor* ) const;

private:
	std::vector<IVarDecl*> varDeclList;
};