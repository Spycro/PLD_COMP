#include "ir/operations/Call.h"
#include "ir/CFG.h"

Call::Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_):IRInstr(bb_),cfg(cfg_){}

void Call::gen_asm(std::ostream &o){
    int i = 0;
    while(i < cfg->params.size() && i < 7){
        switch(i){
            case 1 :
                o   << "\tmovl " << cfg->params.at(i).constValue << ", %edi" <<std::endl;//TODO : a continuer
        }
        ++i;
    }
    o   << "\tmovl "
        << "\tcall " << cfg->label << "()" << std::endl;
}