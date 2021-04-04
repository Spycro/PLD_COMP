#include "ir/operations/Call.h"
#include "ir/CFG.h"

Call::Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_):IRInstr(bb_),cfg(cfg_){}

void Call::gen_asm(std::ostream &o){
    int i = ((cfg->params.size()<6) ? cfg->params.size() : 6)-1;
    while(i >=0){
        switch(i){
            case 0 :
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %edi" <<std::endl;
                break;
            case 1 :
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %esi" <<std::endl;
                break;
            case 2 :
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %edx" <<std::endl;
                break;
            case 3 :
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %ecx" <<std::endl;
                break;
            case 4 :
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %r8d" <<std::endl;
                break;
            case 5:
                o   << "\tmovl " << cfg->params.at(i).getAsm() << ", %r9d" <<std::endl;
                break;
        }
        --i;
    }
    o   << "\tmovl "
        << "\tcall " << cfg->label << "()" << std::endl;
}