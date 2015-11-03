#pragma once
#include "common.h"

class CExpList : public IExpList, public CCoord
{
public:
    CExpList( IExp*, int _line );
    CExpList( const std::vector<IExp*>&, int _line );

    ~CExpList();

	const std::vector<IExp*>& Expressions() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
    std::vector<IExp*> expressions;
};

