#pragma once
#include "common.h"
class CConstructor : public IExp {
public:
    CConstructor( std::string id );
    ~CConstructor();

    std::string Id() const;
    
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    std::string id;
};

