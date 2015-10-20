#pragma once
#include "common.h"
class CNewClass :
    public IExp {
public:
    CNewClass( std::string );
    ~CNewClass();

private:
    std::string id;
};

