#pragma once
#include "Grammar.h"
#include "common.h"
class FormalRestList : public IFormalRestList
{
public:
	FormalRestList( std::vector< IFormalRest* > &_formalRestList );
	~FormalRestList();
//	void Accept( IVisitor* ) const;
private:
	std::vector< IFormalRest* > formalRestList;
};