#pragma once
#include "common.h"

struct CFormalListElement
{
	CFormalListElement( IType* _type, std::string _id ) : type( _type ), id( _id ) {};
	IType* type;
	std::string id;
};

class CFormalList : public IFormalList
{
public:
    CFormalList( CFormalListElement* _decl );
    CFormalList( std::vector<CFormalListElement*>& _list );

	~CFormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<CFormalListElement*>& List() const;

private:
	std::vector<CFormalListElement*> list;
};