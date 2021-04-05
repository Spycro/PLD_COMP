#pragma once

#include "Type.h"
class Int32 : public Type {
    public :

    int getSize(){
        return 8;
    }
    
};
extern Int32 INTTYPE32;