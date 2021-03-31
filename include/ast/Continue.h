#pragma once

#include "Instruction.h"

class Continue : public Instruction {

    public:
        void toString(int n);
        Continue() { }
        virtual ~Continue( ) { }
    private:

};