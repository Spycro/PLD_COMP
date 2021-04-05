#pragma once
#include "../IRInstr.h"

//Lesser than comparison instruction
class Cmp_lt : public IRInstr
{
public:
    Cmp_lt(BasicBlock *bb, SymbolTableElement leftParameter, SymbolTableElement rightParameter, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement leftParameter, rightParameter, d; //leftParameter the value to compare to de reference value, rightParameter the reference value, d the destination value
};
