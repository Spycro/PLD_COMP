#pragma once

#include "Type.h"

class Char : public Type {
    public :

    int getSize(){
        return 4;
    }

    virtual std::string toString() { return "Char"; }

};
