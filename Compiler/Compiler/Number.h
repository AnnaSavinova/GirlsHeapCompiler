#pragma once
#include "common.h"
class CNumber : public IExp, public CCoord
{
public:
    CNumber( int, int _line );
    ~CNumber();

    int Number() const;
    virtual void Accept( IVisitor* visitor ) const
    {
        visitor->Visit( this );
    }
private:
    int number;
};

