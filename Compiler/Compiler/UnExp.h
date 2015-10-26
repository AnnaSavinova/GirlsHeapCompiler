#pragma once
#include "Grammar.h"
#include "common.h"
class CUnExp :
    public IExp {
public:
    CUnExp( IExp*, std::string );
    ~CUnExp();

	const IExp* Expression() const;
	const std::string Operation() const;

private:
    IExp* expression;
    std::string operation;
};

