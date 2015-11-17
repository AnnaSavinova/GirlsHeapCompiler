#pragma once
#include "Frame.h"

class IIRStm {
public:
    IIRStm() {}
    virtual ~IIRStm() {}
};

class CIRStmList {
public:
    CIRStmList( IIRStm* _head, CIRStmList* _tail ) : head( _head ), tail( _tail ) {}

private:
    IIRStm* head;
    CIRStmList* tail;
};

