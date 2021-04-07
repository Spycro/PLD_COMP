#include "ir/instructions/BinaryAnd.h"
#include "ir/ASMConstants.h"

BinaryAnd::BinaryAnd(BasicBlock *bb, SymbolTableElement a_, SymbolTableElement b_, SymbolTableElement res_) : IRInstr(bb), a(a_), b(b_), res(res_){}


void BinaryAnd::gen_asm(std::ostream &o) {

    std::string val1, val2, dest;

    val1 = a.getAsm();
    val2 = b.getAsm();
    dest = res.getAsm();

    o << "\tmovq " << val1 << ", %rax" << std::endl; // We need one parameter to be a register
    o << "\tandq " << val2 << ", %rax" << std::endl;
    o << "\tmovq %rax, " << dest << std::endl;
}
