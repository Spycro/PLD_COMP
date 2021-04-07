#include "ir/instructions/Jmp_continue.h"

#include "ir/BasicBlock.h"

Jmp_continue::Jmp_continue(BasicBlock* bb_) : IRInstr(bb_){}


void Jmp_continue::gen_asm(std::ostream &o) {
        o << "\tjmp " << '.' << bb->label << std::endl; 
}