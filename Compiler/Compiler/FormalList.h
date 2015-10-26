#pragma once
#include "common.h"
class ÑFormalList : public IFormalList
{
public:
	ÑFormalList( IType* _type, std::vector<std::string>& _idList );
	~ÑFormalList();
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
	const IType* Type() const;
	const std::vector<std::string>& IdList() const;

private:
	IType* type;
	std::vector<std::string> idList;
};