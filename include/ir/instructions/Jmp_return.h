#pragma once
#include "../IRInstr.h"

class Jmp_return : public IRInstr
{
public:
    Jmp_return(BasicBlock *bb , CFG* function);

    void gen_asm(std::ostream &o) override;

private:
    CFG* function;
};