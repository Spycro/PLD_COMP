#include "ir/BasicBlock.h"
#include "ir/CFG.h"
#include "ir/instructions/Cmp_eq.h"

int BasicBlock::nextBBnumber = 0;

BasicBlock::BasicBlock(CFG* entry_cfg, std::shared_ptr<Scope> entry_scope, bool entry_needJmp, std::string entry_label)
:cfg(entry_cfg), needJmp(entry_needJmp), label(entry_label), scope(entry_scope){}

void BasicBlock::add_IRInstr(shared_ptr<IRInstr> instruction){
    instrs.push_back(instruction);
}

std::shared_ptr<Scope> BasicBlock::getScope(){
    return scope;
}
const std::shared_ptr<BasicBlock> BasicBlock::getExit_true(){
    return exit_true;
}
const std::shared_ptr<BasicBlock> BasicBlock::getExit_false(){
    return exit_false;
}
const std::shared_ptr<BasicBlock> BasicBlock::getExit_break(){
    if(exit_break != nullptr){
        return exit_break;
    }
    return exit_true;
}
const std::shared_ptr<BasicBlock> BasicBlock::getExit_continue(){
    return exit_continue;
}


void BasicBlock::setExit_true(std::shared_ptr<BasicBlock> exit_true_){
    exit_true = exit_true_;
}
void BasicBlock::setExit_false(std::shared_ptr<BasicBlock> exit_false_){
    exit_false = exit_false_;
}
void BasicBlock::setExit_break(std::shared_ptr<BasicBlock> exit_break_){
    exit_break = exit_break_;
}
void BasicBlock::setExit_continue(std::shared_ptr<BasicBlock> exit_continue_){
    exit_continue = exit_continue_;
}


void BasicBlock::gen_asm(std::ostream &o) {

    o << "." << label << ":" << std::endl;

    for(auto& instr : instrs) {
        if(instr != nullptr) {
            instr->gen_asm(o);
        }
    }

    if(needJmp && exit_true){
        o << "\tjmp ." << exit_true->label << std::endl;
    }    

}