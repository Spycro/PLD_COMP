#include "ir/instructions/Div.h"
#include "ir/ASMConstants.h"

Div::Div(BasicBlock *bb, SymbolTableElement a_, SymbolTableElement b_, SymbolTableElement res_) : IRInstr(bb), a(a_), b(b_), res(res_){}


void Div::gen_asm(std::ostream &o) {

    std::string val1, val2, dest;

    val1 = a.getAsm();
    val2 = b.getAsm();
    dest = res.getAsm();

    o << "\tmovq " << val1 << ", " << RAX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq $0, " << RDX_REGISTER.getAsm() <<std::endl;
    o << "\tmovq " << val2 << ", " << RBX_REGISTER.getAsm() <<std::endl;
    o << "\tidivq " << RBX_REGISTER.getAsm() << std::endl;
    o << "\tmovq " << RAX_REGISTER.getAsm() << ", " << dest << std::endl;

}
