#pragma once
#include "common.h"
class CNewInt :
    public IExp {
public:
    CNewInt( IExp* );
    ~CNewInt();

	const IExp* Expression() const;

private:
    IExp* expression;
};

