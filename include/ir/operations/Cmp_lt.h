#pragma once
#include "../IRInstr.h"

//Lesser than comparison instruction
class Cmp_lt : public IRInstr
{
public:
    Cmp_lt(BasicBlock *bb, SymbolTableElement rightParameter, SymbolTableElement leftParameter, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement rightParameter, leftParameter, d; //rightParameter the reference value, y the value to compare to de reference value, d the destination value
};
