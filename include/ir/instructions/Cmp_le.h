#pragma once
#include "../IRInstr.h"

//Lesser or equal comparison instruction
class Cmp_le : public IRInstr
{
public:
    Cmp_le(BasicBlock *bb, SymbolTableElement leftVal_, SymbolTableElement rightVal_, SymbolTableElement dst_);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftVal, rightVal, dst;
};
