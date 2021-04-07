#include "ir/instructions/Rmem.h"
#include "ir/ASMConstants.h"
#include "ir/ASMx86Utils.h"

using namespace ASMx86Utils;

Rmem::Rmem(BasicBlock *bb, SymbolTableElement addressToRead_, SymbolTableElement out_) : IRInstr(bb), addressToRead(addressToRead_), out(out_){}


void Rmem::gen_asm(std::ostream &o) {

    // Get subregister of RAX (al, ax, eax) depending on out size
    SymbolTableElement& raxSubReg = getSubReg(RAX_REGISTER, out.getSize());

    // Fetch value from memory (4 bytes padding)
    o << "\tmovq " << addressToRead.getAsm() << ", " << RAX_REGISTER.getAsm() << std::endl;
    o << "\tmovq (" << RAX_REGISTER.getAsm() << "), " << RAX_REGISTER.getAsm() << std::endl;

    // Move value from RAX appropriate sub-registry to out
    o << "\tmov" << symbolSizeChar(out.getSize()) << " " << raxSubReg.getAsm() << ", " << out.getAsm() << std::endl;
}
