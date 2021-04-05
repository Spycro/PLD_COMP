#pragma once

#include "Type.h"
class Int32 : public Type {
    public :

    int getSize(){
        return 4;
    }
    
};
extern Int32 INTTYPE32;