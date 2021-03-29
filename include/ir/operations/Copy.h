#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"

class Copy : public IRInstr
{
public:
    Copy(BasicBlock *bb, symbolTableElement x, symbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    symbolTableElement x, d;
};
