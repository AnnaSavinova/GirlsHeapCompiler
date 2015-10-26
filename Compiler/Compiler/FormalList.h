#pragma once
#include "common.h"
class �FormalList : public IFormalList
{
public:
    �FormalList( IVarDecl* _decl );
	�FormalList( std::vector<IVarDecl*>& _list );

	~�FormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IVarDecl*>& List() const;

private:
	std::vector<IVarDecl*> list;
};