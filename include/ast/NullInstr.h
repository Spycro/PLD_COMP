#pragma once

#include "Instruction.h"

class NullInstr : public Instruction
{

public:
    virtual std::string toString() override;

private:
};