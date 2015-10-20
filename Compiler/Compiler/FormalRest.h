#pragma once
#include "common.h"

class CFormalRest : public IFormalRest
{
public:
	CFormalRest( IType* _type, std::string _id );
	~CFormalRest();
	void Accept( IVisitor* ) const;

private:
	IType* type;
	std::string id;
};