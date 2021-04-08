#include "ir/instructions/Modulo.h"
#include "ir/ASMx86Utils.h"
#include "ir/ASMConstants.h"

using namespace ASMx86Utils;

Modulo::Modulo(BasicBlock *bb, SymbolTableElement a_, SymbolTableElement b_, SymbolTableElement res_) : IRInstr(bb), a(a_), b(b_), res(res_){}


void Modulo::gen_asm(std::ostream &o) {

    // Get subregister of RDX (dl, dx, edx) depending on res size
    SymbolTableElement& rdxSubReg = getSubReg(RDX_REGISTER, res.getSize());

    // Convert both operands to 64 bits
    o << moveTo64Reg(a, RAX_REGISTER) << std::endl;
    o << moveTo64Reg(b, RCX_REGISTER) << std::endl;
    o << "\tcqto" << std::endl; // sign extend rax to rdx:rax (128 bits)
    o << "\tidivq " << RCX_REGISTER.getAsm() << std::endl;
    // Move remainder
    o << "\tmov" << symbolSizeChar(res.getSize()) << " " << rdxSubReg.getAsm() << ", " << res.getAsm() << std::endl;

}
