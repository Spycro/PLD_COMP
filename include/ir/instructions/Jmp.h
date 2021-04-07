#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Jmp : public IRInstr
{
public:
    Jmp(BasicBlock *bb, std::shared_ptr<BasicBlock> toJump);

    void gen_asm(std::ostream &o) override;

private:
    std::shared_ptr<BasicBlock> toJump;
};