#include "ir/instructions/Call.h"
#include "ir/CFG.h"
#include "ir/ASMx86Utils.h"
#include "ir/ASMConstants.h"

using namespace ASMx86Utils;

Call::Call(BasicBlock *bb_, CFG* cfg_, std::vector<SymbolTableElement> params_ , SymbolTableElement output_):IRInstr(bb_),cfg(cfg_),params(params_),output(output_){}

void Call::gen_asm(std::ostream &o){

    int nParamsLeft = params.size();
    int nStackVar = 0; // number of variables pushed on the stack

    // If we have more than 6 parameters, push some of them on the stack
    while(nParamsLeft > 6) {
        o << moveTo(params.at(nParamsLeft - 1), RAX_REGISTER) << std::endl;
        o << "\tpushq " << RAX_REGISTER.getAsm() << std::endl;
        --nParamsLeft;
        ++nStackVar;
    }

    SymbolTableElement* reg[] = {&RDI_REGISTER, &RSI_REGISTER, &RDX_REGISTER, &RCX_REGISTER, &R8_REGISTER, &R9_REGISTER};
    int i = 0;

    while(nParamsLeft > 0) {
        o << moveTo(params.at(nParamsLeft - 1), *reg[i]) << std::endl;
        --nParamsLeft;
        ++i;
    }

    o << "\tcall " << cfg->getLabel() << std::endl;

    // Move the stack pointer
    o << "\taddq $" << nStackVar * 8 << ", %rsp"<< std::endl;

    // We don't move the result if the output is void (procedure)
    if(output.getType()->getSize() != 0) {
        o << moveTo(EAX_REGISTER, output) << std::endl;
    }


}