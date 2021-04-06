#include "../../include/ir/CFG.h"

#include "ast/expression/Affectation.h"
#include "ast/expression/Const.h"
#include <memory>
#include "ir/instructions/Copy.h"
#include "type/Int64.h"

CFG::CFG(Function* ast_, std::string label_, Type* type_, std::vector<SymbolTableElement> params_) : ast(ast_), label(label_), type(type_){}

CFG::CFG(shared_ptr<Function> function){
    label = "main"; // todo
    type = &INTTYPE64; //todo

    shared_ptr<Block> block = function->getCode();
    list<shared_ptr<Variable>> parameters = function->getParameters();
    shared_ptr<Scope> scope = block->getScope();
    for(auto var : parameters){
        myParams.push_back(scope->getSymbol(var->getSymbol()));
        incrementVariableCount(1);
    }

    current_bb = std::shared_ptr<BasicBlock>(new BasicBlock(this, scope));
    bbs.push_back(current_bb);
    std::cout<< block->getInstructions().size() <<std::endl;
    for(auto instr : block->getInstructions()){
        inspectInstruction(instr);
    }
}




void CFG::add_bb(shared_ptr<BasicBlock> bb){
    bbs.push_back(bb);    
}
void CFG::incrementVariableCount(int cnt){
    numberOfVariables += cnt;
}


void CFG::gen_asm(std::ostream& o){
    gen_asm_prologue(o);

    for(auto it : bbs){
        it->gen_asm(o);
    }

    gen_asm_epilogue(o);
}

std::string CFG::getLabel(){
    return label;
}

void CFG::gen_asm_prologue(std::ostream& o) {
    o << ".globl " << label << std::endl
               << label << ":" << std::endl
               << "#prologue" << std::endl //prologue
               << "\tpushq %rbp #save rbp on stack" << std::endl
               << "\tmovq %rsp, %rbp #define rbp for current function" << std::endl
               << "\tsubq $" << (numberOfVariables)*8 << ", %rsp #Make room for "<< numberOfVariables  << " variables"<< std::endl; 

    int i = myParams.size()-1;

    int stackPointer = 16 + (i-6)*8;
    while(i>=6){
        o << "\tmovq " << stackPointer<< "(%rbp), %rax" << std::endl;
        o << "\tmovq %rax, " << myParams.at(i)->getAsm()<<std::endl;
        stackPointer -= 8;
        --i;
    }

    while(i >=0){
        switch(i){
            case 0 :
                o   << "\tmovq %rdi, "  << myParams.at(i)->getAsm() <<std::endl;
                break;
            case 1 :
                o   << "\tmovq %rsi, "  << myParams.at(i)->getAsm() <<std::endl;
                break;
            case 2 :
                o   << "\tmovq %rdx, "  << myParams.at(i)->getAsm() <<std::endl;
                break;
            case 3 :
                o   << "\tmovq %rcx, "  << myParams.at(i)->getAsm() <<std::endl;
                break;
            case 4 :
                o   << "\tmovq %r8, "  << myParams.at(i)->getAsm() <<std::endl;
                break;
            case 5:
                o   << "\tmovq %r9, "  << myParams.at(i)->getAsm() <<std::endl;
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

std::shared_ptr<SymbolTableElement> CFG::inspectInstruction(shared_ptr<Instruction> instr){
    std::string instrType = instr->toString();//todo please make this an enum
    if(instrType == "Affectation"){
        shared_ptr<Affectation> affectation = std::dynamic_pointer_cast<Affectation>(instr);
        std::string symbol = affectation->getSymbol();
        shared_ptr<Expression> value = affectation->getValue();
        shared_ptr<Copy> copy (new Copy(current_bb.get(),*inspectInstruction(value),*current_bb->getScope()->getSymbol(symbol)));
        current_bb->add_IRInstr(copy);
    }else if(instrType == "Unary"){

    }else if(instrType == "Const"){
        shared_ptr<Const> myConst = std::dynamic_pointer_cast<Const>(instr);
        return std::shared_ptr<SymbolTableElement>(new SymbolTableElement(&INTTYPE64,std::to_string(myConst->getValue())));
    }else if(instrType == "Variable"){

    }else if(instrType == "Binary"){

    
    }else{
        
    }
    return nullptr;
}