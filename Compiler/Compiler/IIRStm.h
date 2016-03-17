#pragma once
#include <list>
#include "IRTreePrettyPrinter.h"

class IIRStm {
public:
    IIRStm() {}
    virtual void Accept( CIRTreePrettyVisitor* visitor ) const = 0;
    virtual ~IIRStm() {}
};
