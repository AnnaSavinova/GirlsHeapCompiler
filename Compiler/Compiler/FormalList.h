#pragma once
#include "common.h"

struct CFormalListElement
{
	CFormalListElement( IType* _type, std::string _id, int _line ) : type( _type ) 
  {
    id = symbolStorage.Get(_id);
  };
	IType* type;
  CSymbol* id;
};

class CFormalList : public IFormalList, public CCoord
{
public:
    CFormalList( CFormalListElement* _decl, int _line );
    CFormalList( std::vector<CFormalListElement*>& _list, int _line );

	~CFormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const std::vector<CFormalListElement*>& List() const;

private:
	std::vector<CFormalListElement*> list;
};