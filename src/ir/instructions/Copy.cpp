#include "ir/instructions/Copy.h"
#include "ir/ASMx86Utils.h"
#include "ir/ASMConstants.h"

using namespace ASMx86Utils;

Copy::Copy(BasicBlock* bb, SymbolTableElement inputX, SymbolTableElement inputD) : IRInstr(bb), d(inputD), x(inputX){}

void Copy::gen_asm(std::ostream &o) {
    // Get subregister of RAX (al, ax, eax) depending on dest size
    SymbolTableElement& raxSubReg = getSubReg(RAX_REGISTER, d.getSize());

    // Move (and convert) x to 64 bits RAX register
    o << moveTo64Reg(x, RAX_REGISTER) << std::endl;
    o << "\tmov" << symbolSizeChar(d.getSize()) << " " << raxSubReg.getAsm() << ", " << d.getAsm() << std::endl;   
}