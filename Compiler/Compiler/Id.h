#pragma once
#include "common.h"

class CId : public IExp {
public:
    CId( std::string );
    ~CId();

    std::string Id() const;
private:
    std::string id;
};

