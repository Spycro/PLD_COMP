#include "../../include/ir/CFG.h"


CFG::CFG(Function* ast_, std::string label_, Type* type_, std::vector<SymbolTableElement> params_) : ast(ast_), label(label_), type(type_), params(params_) {}

void CFG::add_bb(BasicBlock* bb){
    bbs.push_back(bb);    
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
               << "\tmovq %rsp, %rbp #define rbp for current function" << std::endl;
               
    int i = ((params.size()<6) ? params.size() : 6)-1;
    while(i >=0){
        switch(i){
            case 0 :
                o   << "\tmovl %edi, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 1 :
                o   << "\tmovl %esi, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 2 :
                o   << "\tmovl %edx, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 3 :
                o   << "\tmovl %ecx, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 4 :
                o   << "\tmovl %r8d, "  << params.at(i).getAsm() <<std::endl;
                break;
            case 5:
                o   << "\tmovl %r9d, "  << params.at(i).getAsm() <<std::endl;
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
    o   << "\tpopq %rbp #restore rbp from stack\n"
        << "\tret\n";
}