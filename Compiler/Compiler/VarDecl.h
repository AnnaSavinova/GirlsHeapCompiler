#pragma once
#include "common.h"
class CVarDecl : public IVarDecl
{
public:
	CVarDecl( IType* _type, std::string _id  );
	~CVarDecl();
//	void Accept( IVisitor* ) const;
private:
	IType* type;
	std::string id;
};