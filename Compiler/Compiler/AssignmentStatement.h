#pragma once
#include "common.h"

class CAssignmentStatement : public IStatement, public CCoord {
public:
    CAssignmentStatement( std::string, IExp*, int _line );
    ~CAssignmentStatement();

	const CSymbol* Id() const;
	const IExp* Expression() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
    const CSymbol* id;
    IExp* expression;
};

