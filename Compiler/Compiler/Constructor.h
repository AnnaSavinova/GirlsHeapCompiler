#pragma once
#include "common.h"
class CConstructor : public IExp {
public:
    CConstructor( std::string id );
    ~CConstructor();

    std::string Id() const;
private:
    std::string id;
};

