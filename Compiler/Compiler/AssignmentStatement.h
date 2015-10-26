#pragma once
#include "common.h"

class CAssignmentStatement : public IStatement {
public:
    CAssignmentStatement( std::string, IExp* );
    ~CAssignmentStatement();

	const std::string Id() const;
	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
    std::string id;
    IExp* expression;
};

