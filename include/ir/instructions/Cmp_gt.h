#pragma once
#include "../IRInstr.h"

//Lesser or equal comparison instruction
class Cmp_gt : public IRInstr
{
public:
    Cmp_gt(BasicBlock *bb, SymbolTableElement leftVal_, SymbolTableElement rightVal_, SymbolTableElement dst_);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftVal, rightVal, dst;
};
