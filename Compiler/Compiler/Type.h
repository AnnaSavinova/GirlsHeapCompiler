#pragma once
#include "common.h"

class CType : public IType, public CCoord {
public:
    CType( const std::string, int _line );
    ~CType();

	const std::string Type() const;
	void Accept( IVisitor* visitor ) const
	{
		visitor->Visit( this );
	}
private:
	std::string type;
};

