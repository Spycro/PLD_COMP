#pragma once

#include "../Instruction.h"

class Expression : public Instruction
{

public:
    virtual std::string toString() override;

private:
};
