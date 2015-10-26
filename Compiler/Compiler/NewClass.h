#pragma once
#include "Grammar.h"
#include "common.h"
class CNewClass :
    public IExp {
public:
    CNewClass( std::string );
    ~CNewClass();

	const std::string Id() const;

private:
    std::string id;
};

