#pragma once
#include "common.h"

class CId : public IExp, public CCoord
{
public:
    CId( std::string, int _line );
    ~CId();

    std::string Id() const; 
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    std::string id;
};

