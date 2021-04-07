#include "ir/instructions/putChar.h"
#include "ir/ASMConstants.h"

putChar::putChar(BasicBlock *bb, SymbolTableElement charToPrint_) : IRInstr(bb), charToPrint(charToPrint_) {}


void putChar::gen_asm(std::ostream &o) {

    o << "\tsubq $8, %rsp #Make room for 1 variable"<< std::endl; 

    o << "\tmovq $1, %rax #sys_write syscall" <<std::endl;
    o << "\tmovb " << charToPrint.getAsm() << ", -4(%rsp)  #store char" << std::endl;
    o << "\tmovq $1, %rdi #stdout" << std::endl;
    o << "\tleaq -4(%rsp), %rsi #pointer of the char" << std::endl;
    o << "\tmovq $1, %rdx # length = 1" << std::endl;
    o << "\tsyscall" << std::endl;

    o << "\taddq $8, %rsp #remove local variable from stack"<< std::endl;
}
