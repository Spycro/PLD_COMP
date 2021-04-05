#pragma once
#include "../IRInstr.h"

//Lesser or equal comparison instruction
class Cmp_ge : public IRInstr
{
public:
    Cmp_ge(BasicBlock *bb, SymbolTableElement rightParameter, SymbolTableElement leftParameter, SymbolTableElement d);

    void gen_asm(std::ostream &o) override;

private:
    SymbolTableElement rightParameter, leftParameter, d; //rightParameter the reference value, y the value to compare to de reference value, d the destination value
};
