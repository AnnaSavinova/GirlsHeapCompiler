#pragma once
#include "Grammar.h"
#include "common.h"
class CVarDecl : public IVarDecl, public CCoord
{
public:
	CVarDecl( IType* _type, std::string _id, int _line );
	~CVarDecl();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

	const IType* Type() const;
	CSymbol* Id() const;

private:
	IType* type;
  CSymbol* id;
};