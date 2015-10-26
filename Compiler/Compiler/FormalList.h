#pragma once
#include "common.h"
class ÑFormalList : public IFormalList
{
public:
    ÑFormalList( IVarDecl* _decl );
	ÑFormalList( std::vector<IVarDecl*>& _list );

	~ÑFormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IVarDecl*>& List() const;

private:
	std::vector<IVarDecl*> list;
};