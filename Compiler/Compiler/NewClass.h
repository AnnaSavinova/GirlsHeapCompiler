#pragma once
#include "common.h"
class CNewClass :
    public IExp {
public:
    CNewClass( std::string );
    ~CNewClass();

	const std::string Id() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}

private:
    std::string id;
};

