#include "ir/instructions/Call.h"
#include "ir/CFG.h"

Call::Call(BasicBlock *bb_, std::shared_ptr<CFG> cfg_, std::vector<SymbolTableElement> params_ , SymbolTableElement output_):IRInstr(bb_),cfg(cfg_),params(params_),output(output_){}

void Call::gen_asm(std::ostream &o){
    int redimCounter = 0;
    int i = params.size()-1;
    while(i>=6){
        o << "\tpushq " << params.at(i).getAsm()<<std::endl;
        --i;
        ++redimCounter;
    }
    while(i >=0){
        switch(i){
            case 0 :
                o   << "\tmovq " << params.at(i).getAsm() << ", %rdi" <<std::endl;
                break;
            case 1 :
                o   << "\tmovq " << params.at(i).getAsm() << ", %rsi" <<std::endl;
                break;
            case 2 :
                o   << "\tmovq " << params.at(i).getAsm() << ", %rdx" <<std::endl;
                break;
            case 3 :
                o   << "\tmovq " << params.at(i).getAsm() << ", %rcx" <<std::endl;
                break;
            case 4 :
                o   << "\tmovq " << params.at(i).getAsm() << ", %r8" <<std::endl;
                break;
            case 5:
                o   << "\tmovq " << params.at(i).getAsm() << ", %r9" <<std::endl;
                break;
        }
        --i;
    }
    o << "\tcall " << cfg->label << std::endl
        << "\taddq $" << redimCounter * 8 << ", %rsp"<< std::endl
        << "\tmovl %eax, "  << output.getAsm() <<std::endl;
}