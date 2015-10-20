#pragma once
#include "common.h"

class FormalRest : public IFormalRest
{
public:
	FormalRest( IType* _type, std::string _id );
	~FormalRest();
//	void Accept( IVisitor* ) const;
private:
	IType* type;
	std::string id;
};