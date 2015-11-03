#pragma once
#include "common.h"

class CId : public IExp, public CCoord
{
public:
    CId( std::string, int _line );
    ~CId();

    CSymbol* Id() const; 
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    CSymbol* id;
};

