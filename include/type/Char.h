#pragma once

#include "Type.h"

class Char : public Type {
    public :

    int getSize() override {
        return 4;
    }

    virtual std::string toString() override { return "Char"; }

};
