#include "ir/operations/Call.h"

Call::Call(BasicBlock *bb_, std::string functionName_):IRInstr(bb_),functionName(functionName_){}

void Call::gen_asm(std::ostream &o){
    o << "\tcall" << functionName << "()" << std::endl;
}