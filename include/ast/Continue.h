#pragma once

#include "Instruction.h"

class Continue : public Instruction
{
    public:
        Continue() { }

        virtual std::string toString() override;

    private:
};