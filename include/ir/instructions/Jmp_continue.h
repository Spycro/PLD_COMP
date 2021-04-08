#pragma once
#include "../IRInstr.h"

class Jmp_continue : public IRInstr
{
public:
    Jmp_continue(BasicBlock *bb);

    void gen_asm(std::ostream &o) override;

private:
};