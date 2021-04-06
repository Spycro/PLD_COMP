#pragma once
#include "Instruction.h"

class Break : public Instruction
{
    public:        
        Break() { type=BREAK; }
        
        virtual std::string toString() override;

    private:
};