#pragma once
#include "../IRInstr.h"

class Jmp_break : public IRInstr
{
public:
    Jmp_break(BasicBlock *bb);

    void gen_asm(std::ostream &o) override;

private:
};