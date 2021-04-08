#pragma once
#include "../IRInstr.h"

//Lesser than comparison instruction
class Cmp_lt : public IRInstr
{
public:
    Cmp_lt(BasicBlock *bb, SymbolTableElement leftVal_, SymbolTableElement rightVal_, SymbolTableElement dst_);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftVal, rightVal, dst;
};
