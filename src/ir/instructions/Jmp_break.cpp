#include "ir/instructions/Jmp_break.h"

#include "ir/BasicBlock.h"

Jmp_break::Jmp_break(BasicBlock* bb_) : IRInstr(bb_){}


void Jmp_break::gen_asm(std::ostream &o) {
    if(bb->getExit_break()){
        o << "\tjmp " << '.' << bb->getExit_break()->label << std::endl; 
    }
}