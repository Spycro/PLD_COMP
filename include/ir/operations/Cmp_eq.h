#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

//Equal comparison instruction
class Cmp_eq : public IRInstr
{
public:
    Cmp_eq(BasicBlock *bb, symbolTableElement x, symbolTableElement y, symbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    symbolTableElement x, y, d;
};
