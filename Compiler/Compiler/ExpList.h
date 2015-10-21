#pragma once
#include "common.h"
class CExpList :
    public IExpList {
public:
    CExpList( const std::vector<IExp*>& );
    ~CExpList();

	const std::vector<IExp*>* Expressions() const;

private:
    std::vector<IExp*> expressions;
};

