#include "ir/IRInstr.h"

IRInstr::IRInstr(BasicBlock* bb_) : bb(bb_) {}

std::string IRInstr::asmAdaptInstruction(std::string instr,SymbolTableElement* el1, SymbolTableElement* el2, SymbolTableElement* el3){
    int size = el1->getSize();
    if(el2){
        size = (size<el2->getSize())? size : el2->getSize();
    }
    if(el3){
        size = (size<el3->getSize())? size : el3->getSize();
    }
    
    if(size == 1){
        instr.append("b");
    }else if(size == 2){
        instr.append("w");
    }else if(size <= 4){
        instr.append("l");
    }else{
        instr.append("q");
    }
    return instr;
}