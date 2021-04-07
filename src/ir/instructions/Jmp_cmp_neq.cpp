#include "ir/instructions/Jmp_cmp_neq.h"
#include "ir/BasicBlock.h"
#include "ir/ASMConstants.h"
#include "ir/ASMx86Utils.h"

using namespace ASMx86Utils;

Jmp_cmp_neq::Jmp_cmp_neq(BasicBlock* bb_, SymbolTableElement x_, SymbolTableElement y_) : IRInstr(bb_), x(x_), y(y_){}


void Jmp_cmp_neq::gen_asm(std::ostream &o) {
    // Convert both operands to 64 bits
    o << moveTo64Reg(x, RAX_REGISTER) << std::endl;
    o << moveTo64Reg(y, RDX_REGISTER) << std::endl;

    // Perform 64 bits comparison
    o << "\tcmpq " << RDX_REGISTER.getAsm() << ", " << RAX_REGISTER.getAsm() << std::endl;
    o << "\tje " << '.' << bb->getExit_false()->label << std::endl;
}