#include "ir/operations/Call.h"
#include "ir/CFG.h"

Call::Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_):IRInstr(bb_),cfg(cfg_){}

void Call::gen_asm(std::ostream &o){
    o << "\tcall " << cfg->label << "()" << std::endl;
}