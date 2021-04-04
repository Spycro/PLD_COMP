#pragma once

#include "Type.h"
class Void : public Type {
    public :

    int getSize(){
        return 0;
    }
    
};

extern Void VOIDTYPE;