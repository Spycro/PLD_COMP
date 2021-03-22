#include "../../include/ir/BasicBlock.h"
#include "../../include/ir/CFG.h"

BasicBlock::BasicBlock(std::shared_ptr<CFG> entry_cfg, std::string entry_label, std::shared_ptr<Scope> entry_scope)
:cfg(entry_cfg), label(entry_label), scope(entry_scope){}

void BasicBlock::add_IRInstr(IRInstr* instruction){
    instrs.push_back(instruction);
}

void BasicBlock::gen_asm(std::ostream &o) {

    for(auto& instr : instrs) {
        instr->gen_asm(o);
    }

}