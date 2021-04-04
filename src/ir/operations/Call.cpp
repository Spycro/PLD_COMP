#include "ir/operations/Call.h"
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
                o   << "\tmovl " << params.at(i).getAsm() << ", %edi" <<std::endl;
                break;
            case 1 :
                o   << "\tmovl " << params.at(i).getAsm() << ", %esi" <<std::endl;
                break;
            case 2 :
                o   << "\tmovl " << params.at(i).getAsm() << ", %edx" <<std::endl;
                break;
            case 3 :
                o   << "\tmovl " << params.at(i).getAsm() << ", %ecx" <<std::endl;
                break;
            case 4 :
                o   << "\tmovl " << params.at(i).getAsm() << ", %r8d" <<std::endl;
                break;
            case 5:
                o   << "\tmovl " << params.at(i).getAsm() << ", %r9d" <<std::endl;
                break;
        }
        --i;
    }
    o << "\tcall " << cfg->label << std::endl
        << "\taddq $" << redimCounter * 8 << ", %rsp"<< std::endl
        << "\tmovl %eax, "  << output.getAsm() <<std::endl;
}