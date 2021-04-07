#pragma once

#include "Type.h"
class Int16 : public Type {
    public :

    int getSize(){
        return 2;
    }
    
};
extern Int16 INTTYPE16;