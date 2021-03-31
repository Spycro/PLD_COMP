#pragma once
#include "Instruction.h"

class Break : public Instruction
{

public:
    virtual std::string toString() override;

private:
};