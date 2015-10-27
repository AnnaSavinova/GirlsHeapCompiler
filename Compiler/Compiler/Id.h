#pragma once
#include "common.h"

class CId : public IExp {
public:
    CId( std::string );
    ~CId();

    std::string Id() const; 
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    std::string id;
};

