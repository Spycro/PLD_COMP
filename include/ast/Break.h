#pragma once
#include "Instruction.h"

class Break : public Instruction
{
    public:        
        Break() { }
        
        virtual std::string toString() override;

    private:
};