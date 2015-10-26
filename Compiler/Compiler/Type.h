#pragma once
#include "common.h"

class CType : public IType {
public:
    CType( const std::string );
    ~CType();

	const std::string Type() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
	std::string type;
};

