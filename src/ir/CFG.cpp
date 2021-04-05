#include "../../include/ir/CFG.h"


CFG::CFG(Function* ast_, std::string label_, Type* type_, std::vector<SymbolTableElement> params_) : ast(ast_), label(label_), type(type_), params(params_) {}

void CFG::add_bb(BasicBlock* bb){
    bbs.push_back(bb);    
}
void CFG::incrementVariableCount(int cnt){
    numberOfVariables += cnt;
}

void CFG::gen_asm(std::ostream& o){
    gen_asm_prologue(o);

    vector<BasicBlock*>::iterator it;
    for(it = bbs.begin(); it != bbs.end(); it++){
        (*it)->gen_asm(o);
    }

    gen_asm_epilogue(o);
}

void CFG::gen_asm_prologue(std::ostream& o) {
    o << ".globl " << label << std::endl
               << label << ":" << std::endl
               << "#prologue" << std::endl //prologue
               << "\tpushq %rbp #save rbp on stack" << std::endl
               << "\tmovq %rsp, %rbp #define rbp for current function" << std::endl
               << "\tsubq $" << (numberOfVariables)*8 << ", %rsp #Make room for "<< numberOfVariables  << " variables"<< std::endl; 

    int i = params.size()-1;

    int stackPointer = 16 + (i-6)*8;
    while(i>=6){
        o << "\tmovq " << stackPointer<< "(%rbp), %rax" << std::endl;
        o << "\tmovq %rax, " << params.at(i).getAsm()<<std::endl;
        stackPointer -= 8;
        --i;
    }

    while(i >=0){
        switch(i){
            case 0 :
                o   << "\tmovq %rdi, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 1 :
                o   << "\tmovq %rsi, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 2 :
                o   << "\tmovq %rdx, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 3 :
                o   << "\tmovq %rcx, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 4 :
                o   << "\tmovq %r8, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 5:
                o   << "\tmovq %r9, "  << params.at(i).getAsm() <<std::endl;
                break;
        }
        --i;
    }
}

void CFG::gen_asm_epilogue(std::ostream& o) {
    o <<       "#epilogue\n" ;// the epilogue
    if(type==&VOIDTYPE){
        o << "\tnop\n";
    }
    o << "\taddq $" << (numberOfVariables)*8 << ", %rsp #remove all local variables from stack"<< std::endl
        << "\tpopq %rbp #restore rbp from stack\n"
        << "\tret\n";
}