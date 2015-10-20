#pragma once
#include "common.h"

class FormalList : public IFormalList
{
public:
	FormalList( IType* _type, std::string _id,
		IFormalRestList* _formalRestList );
	~FormalList();
	void Accept( IVisitor* ) const;
private:
	IType* type;
	std::string id;
	IFormalRestList* formalRestList;
};