#pragma once

#include "Type.h"
class Int64 : public Type {
    public :

    int getSize(){
        return 8;
    }
    
};
extern Int64 INTTYPE64;