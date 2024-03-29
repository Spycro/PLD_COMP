#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Jmp_cmp_eq : public IRInstr
{
public:
    Jmp_cmp_eq(BasicBlock *bb, SymbolTableElement x, SymbolTableElement y);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement x, y;
};
