#pragma once
#include "common.h"
class CNumber : public IExp {
public:
    CNumber( int );
    ~CNumber();

    int Number() const;
private:
    int number;
};

