#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"
#include "ir/CFG.h"

class Call : public IRInstr
{
public:
    Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_, std::vector<SymbolTableElement> params_ , SymbolTableElement output_);

    void gen_asm(std::ostream &o) override;

private:
    std::shared_ptr<CFG> cfg;
    std::vector<SymbolTableElement> params;
    SymbolTableElement output;
};

