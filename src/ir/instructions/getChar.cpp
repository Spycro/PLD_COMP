#include "ir/instructions/getChar.h"
#include "ir/ASMConstants.h"

getChar::getChar(BasicBlock *bb, SymbolTableElement charDest_) : IRInstr(bb), charDest(charDest_) {}


void getChar::gen_asm(std::ostream &o) {

    o << "\tsubq $8, %rsp #Make room for 1 variable"<< std::endl; 

    o << "\tmovq $0, %rax #sys_read syscall" <<std::endl;
    o << "\tmovq $0, %rdi #stdin" << std::endl;
    if(charDest.getType() != &VOIDTYPE){
        o << "\tleaq " << charDest.getAsm() << ", %rsi #char addr destination" << std::endl;
    }
    o << "\tmovq $1, %rdx # length = 1" << std::endl;
    o << "\tsyscall" << std::endl;

    o << "\taddq $8, %rsp #remove local variable from stack"<< std::endl;
}
