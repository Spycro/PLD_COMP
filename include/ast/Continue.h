#pragma once

#include "Instruction.h"

class Continue : public Instruction
{
    public:
        Continue() { type = CONTINUE; }

        virtual std::string toString() override;

    private:
};