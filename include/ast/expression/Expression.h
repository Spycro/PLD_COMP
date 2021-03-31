#pragma once

#include "../Instruction.h"


class Expression : public Instruction {

    public:
        virtual void toString(int n);
        
        Expression() {}
        virtual ~Expression() {};
    private:

};
