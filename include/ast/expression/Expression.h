#pragma once

#include "../Instruction.h"
#include <iostream>

class Expression : public Instruction {

    public:
        virtual void toString(int n);
    private:

};
