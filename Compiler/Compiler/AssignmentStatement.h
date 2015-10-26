#pragma once
#include "Grammar.h"
#include "common.h"
class CAssignmentStatement : public IStatement {
public:
    CAssignmentStatement( std::string, IExp* );
    ~CAssignmentStatement();

	const std::string Id() const;
	const IExp* Expression() const;

private:
    std::string id;
    IExp* expression;
};

