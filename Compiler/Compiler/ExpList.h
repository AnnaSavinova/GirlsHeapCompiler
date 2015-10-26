#pragma once
#include "Grammar.h"
#include "common.h"
#include <vector>
class CExpList : public IExpList {
public:
    CExpList( const std::vector<IExp*>& );
    ~CExpList();

	const std::vector<IExp*>* Expressions() const;

private:
    std::vector<IExp*> expressions;
};

