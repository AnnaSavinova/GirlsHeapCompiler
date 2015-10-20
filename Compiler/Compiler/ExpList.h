#pragma once
#include "common.h"
class CExpList :
    public IExpList {
public:
    CExpList( const std::vector<IExp*>& );
    ~CExpList();

private:
    std::vector<IExp*> expressions;
};

