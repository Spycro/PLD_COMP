#pragma once

#include "Instruction.h"

class NullInstr : public Instruction
{
    public:
        NullInstr( ) {}
        virtual std::string toString() override;

    private:
};