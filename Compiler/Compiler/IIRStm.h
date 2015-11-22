#pragma once
#include "Frame.h"
#include <list>

class IIRStm {
public:
    IIRStm() {}
    virtual ~IIRStm() {}
};

class CIRStmList {
public:
    CIRStmList(IIRStm* head, CIRStmList* tail);
    std::list<IIRStm> GetStmList();

private:
    std::list<IIRStm> stmList;
};

