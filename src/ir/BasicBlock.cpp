#include "ir/BasicBlock.h"
#include "ir/CFG.h"
#include "ir/instructions/Cmp_eq.h"

int BasicBlock::nextBBnumber = 0;

BasicBlock::BasicBlock(std::shared_ptr<CFG> entry_cfg, std::shared_ptr<Scope> entry_scope, bool entry_needJmp, std::string entry_label)
:cfg(entry_cfg), needJmp(entry_needJmp), label(entry_label), scope(entry_scope){}

void BasicBlock::add_IRInstr(IRInstr* instruction){
    instrs.push_back(instruction);
}

void BasicBlock::gen_asm(std::ostream &o) {

    o << "." << label << ":" << std::endl;

    for(auto& instr : instrs) {
        instr->gen_asm(o);
    }

    if(needJmp){
        o << "\tjmp ." << exit_true->label << std::endl;
    }    

}