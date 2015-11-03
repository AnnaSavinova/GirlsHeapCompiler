#pragma once
#include "common.h"
class CConstructor : public IExp, public CCoord
{
public:
    CConstructor( std::string id, int _line );
    ~CConstructor();

	CSymbol* Id() const;
    
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    CSymbol* id;
};

