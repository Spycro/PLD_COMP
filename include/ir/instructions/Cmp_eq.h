#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

//Equal comparison instruction
class Cmp_eq : public IRInstr
{
public:
    Cmp_eq(BasicBlock *bb, SymbolTableElement leftVal_, SymbolTableElement rightVal_, SymbolTableElement dst_);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftVal, rightVal, dst;
};
