#pragma once

#include "Instruction.h"

class Continue : public Instruction
{

public:
    virtual std::string toString() override;

private:
};