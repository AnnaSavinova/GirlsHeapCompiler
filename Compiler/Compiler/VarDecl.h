#pragma once
#include "Grammar.h"
#include "common.h"
class CVarDecl : public IVarDecl
{
public:
	CVarDecl( IType* _type, std::string _id  );
	~CVarDecl();
	void Accept( IVisitor* ) const;

	const IType* Type() const;
	const std::string Id() const;

private:
	IType* type;
	std::string id;
};