#pragma once

#include "Type.h"

class Int : public Type {
    public :

    int getSize() override {
        return 8;
    }

    virtual std::string toString() override { return "Int"; }
    
};
