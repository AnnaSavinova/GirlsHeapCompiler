#pragma once
#include "common.h"
class CFormalList : public IFormalList
{
public:
    CFormalList( IVarDecl* _decl );
    CFormalList( std::vector<IVarDecl*>& _list );

	~CFormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<IVarDecl*>& List() const;

private:
	std::vector<IVarDecl*> list;
};