#pragma once

#include "Type.h"

class Int : public Type {
    public :

    int getSize(){
        return 8;
    }

    virtual std::string toString() { return "Int"; }
    
};
