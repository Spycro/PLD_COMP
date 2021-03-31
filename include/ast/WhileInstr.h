#pragma once

#include "ControlStructure.h"

class WhileInstr : public ControlStructure {

    public:
        void toString(int n);
        WhileInstr() { }
        virtual ~WhileInstr () { }
    private:


};