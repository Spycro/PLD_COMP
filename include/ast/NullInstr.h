#pragma once

#include "Instruction.h"

class NullInstr : public Instruction
{
    public:
        NullInstr( ) { type=NULLINSTR; }
        virtual std::string toString() override;

    private:
};