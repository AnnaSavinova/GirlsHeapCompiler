#pragma once
#include "common.h"

class ÑFormalList : public IFormalList
{
public:
	ÑFormalList( IType* _type, std::string _id,
		IFormalRestList* _formalRestList );
	~ÑFormalList();
	void Accept( IVisitor* ) const;

private:
	IType* type;
	std::string id;
	IFormalRestList* formalRestList;
};