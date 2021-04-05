#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

//Equal comparison instruction
class Cmp_neq : public IRInstr
{
public:
    Cmp_neq(BasicBlock *bb, SymbolTableElement x, SymbolTableElement y, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement x, y, d;
};
