#pragma once
#include "Grammar.h"
#include "common.h"
class CLengthExp : public IExp {
public:
    CLengthExp( IExp* );
    ~CLengthExp();

	const IExp* Expression() const;

private:
    IExp* expression;
};

