#pragma once
#include <list>
#include "IRTreePrettyPrinter.h"

class IIRStm {
public:
    IIRStm() {}
    virtual const CIRExpList* Kids() const = 0;
    virtual const IIRStm* Build( const CIRExpList* ) const = 0;
    virtual void Accept( CIRTreePrettyVisitor* visitor ) const = 0;
    virtual ~IIRStm() {}
};
