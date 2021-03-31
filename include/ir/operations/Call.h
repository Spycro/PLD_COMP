#pragma once
#include "../IRInstr.h"
#include "SymbolTable.h"
#include "ir/CFG.h"

class Call : public IRInstr
{
public:
    Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_);

    void gen_asm(std::ostream &o) override;

private:
    std::shared_ptr<CFG> cfg;
};

