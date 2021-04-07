#include "ir/instructions/Sub.h"
#include "ir/ASMx86Utils.h"
#include "ir/ASMConstants.h"

using namespace ASMx86Utils;

Sub::Sub(BasicBlock *bb, SymbolTableElement a_, SymbolTableElement b_, SymbolTableElement res_) : IRInstr(bb), a(a_), b(b_), res(res_){}

void Sub::gen_asm(std::ostream &o) {
    // Get subregister of RAX (al, ax, eax) depending on res size
    SymbolTableElement& raxSubReg = getSubReg(RAX_REGISTER, res.getSize());

    // Convert both operands to 64 bits
    o << moveTo64Reg(a, RAX_REGISTER) << std::endl;
    o << moveTo64Reg(b, RDX_REGISTER) << std::endl;

    // Perform 64 bits subtraction
    o << "\tsubq " << RAX_REGISTER.getAsm() << ", " << RDX_REGISTER.getAsm() << std::endl;
    o << "\tmov" << symbolSizeChar(res.getSize()) << " " << raxSubReg.getAsm() << ", " << res.getAsm() << std::endl;   
}

