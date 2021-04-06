#include "../../include/ir/CFG.h"

#include "ast/expression/Affectation.h"
#include "ast/expression/Const.h"
#include "ast/expression/Binary.h"
#include <memory>
#include "ir/instructions/Add.h"
#include "ir/instructions/Sub.h"
#include "ir/instructions/Mul.h"
#include "ir/instructions/Div.h"
#include "ir/instructions/Copy.h"
#include "type/Int64.h"
#include "ir/ASMConstants.h"

CFG::CFG(Function* ast_, std::string label_, VarType::Type* type_, std::vector<SymbolTableElement> params_) : ast(ast_), label(label_), type(type_){}

CFG::CFG(shared_ptr<Node> function){
    label = "main"; // todo
    type = &INTTYPE64; //todo

    shared_ptr<Node> block = function->getCode();
    list<shared_ptr<Node>> parameters = function->getParameters();
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
    current_bb = bb;
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

std::shared_ptr<SymbolTableElement> CFG::inspectInstruction(shared_ptr<Node> instr){
    std::cout<<instr->toString() << " enum: " << instr->getType()<<std::endl;
    switch (instr->getType())
    {
    case NodeType::AFFECTATION:
        {
            std::string symbol = instr->getSymbol();
            shared_ptr<Node> value = instr->getValue();

            std::shared_ptr<SymbolTableElement> input = inspectInstruction(value);
            std::shared_ptr<SymbolTableElement> output = current_bb->getScope()->getSymbol(symbol);

            shared_ptr<Copy> copy (new Copy(current_bb.get(),*input,*output));
            current_bb->add_IRInstr(copy);
            return output;
        }
        break;

    case NodeType::CONST:
        {
            shared_ptr<Const> myConst = std::dynamic_pointer_cast<Const>(instr);
            std::cout<< "Const value: " << myConst->getConstValue()<< std::endl;
            return std::shared_ptr<SymbolTableElement>(new SymbolTableElement(&INTTYPE64,std::to_string(myConst->getConstValue())));
        }
        break;
    
    case NodeType::VARIABLE:
        {
            shared_ptr<Variable> myVar = std::dynamic_pointer_cast<Variable>(instr);
            return current_bb->getScope()->getSymbol(myVar->getSymbol());
        }
        break;

    case NodeType::RETURN:
        {
            shared_ptr<Node> valToReturn = instr->getValue(); //todo get instruction for return
            shared_ptr<Copy> copy (new Copy(current_bb.get(),*inspectInstruction(valToReturn),RAX_REGISTER));
            current_bb->add_IRInstr(copy);
        }
        break;

    case NodeType::BINARY:
        {
            shared_ptr<SymbolTableElement> leftOp= inspectInstruction(instr->getOperand1());
            shared_ptr<SymbolTableElement> rightOp = inspectInstruction(instr->getOperand2());
            shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(&INTTYPE64);
            shared_ptr<IRInstr> op;
            std::cout << instr->getOp() <<std::endl;

            switch (instr->getOp())
            {
            case BinaryOperator::PLUS:
                op = shared_ptr<Add>(new Add(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::MINUS:
                op = shared_ptr<Sub>(new Sub(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::MULT:
                op = shared_ptr<Mul>(new Mul(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::DIV:
                op = shared_ptr<Div>(new Div(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            
            default:
                break;
            }
            current_bb->add_IRInstr(op);
            return res;
        }
        break;
    case NodeType::INFINSTR:
        {
            shared_ptr<SymbolTableElement> condition = inspectInstruction(instr->getTest());
            shared_ptr<Node> mainBlock = instr->getCode();
            shared_ptr<Node> elseBlock = instr->getCodeElse();

 
            shared_ptr<BasicBlock> startBlock = current_bb;
            shared_ptr<BasicBlock> mainBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
            shared_ptr<BasicBlock> endBlock(new BasicBlock(this, current_bb->getScope()));
            

            startBlock->setExit_true(mainBasicBlock);
            
            
            mainBasicBlock->setExit_true(endBlock);

            if(elseBlock == nullptr){
                startBlock->setExit_false(endBlock);
            }else if(elseBlock->getType() == NodeType::BLOCK){
                shared_ptr<BasicBlock> elseBasicBlock(new BasicBlock(this,elseBlock->getScope(),true));

                startBlock->setExit_false(elseBasicBlock);
                elseBasicBlock->setExit_true(endBlock);

                add_bb(mainBasicBlock);

                for(auto InstrInBlock : elseBlock->getInstructions()){ 
                    inspectInstruction(InstrInBlock);
                }
            }else{
                shared_ptr<BasicBlock> elseBasicBlock(new BasicBlock(this,elseBlock->getScope(),true));
                startBlock->setExit_false(elseBasicBlock);
                add_bb(elseBasicBlock);
                inspectInstruction(elseBlock);
                current_bb->setExit_true(endBlock);
            }

            add_bb(mainBasicBlock);
            for(auto InstrInBlock : mainBlock->getInstructions()){ 
                inspectInstruction(InstrInBlock);
            }


            add_bb(endBlock);
        }
        break;
    case NodeType::BLOCK:
        {
            shared_ptr<Scope> scope = instr->getScope(); //todo get scope
            current_bb->setExit_true(std::shared_ptr<BasicBlock>(new BasicBlock(this, scope)));
            add_bb(current_bb->getExit_true());
            for(auto InstrInBlock : instr->getInstructions()){ //todo go through instructions
                inspectInstruction(InstrInBlock);
            }
            current_bb->setExit_true(std::shared_ptr<BasicBlock>(new BasicBlock(this, scope->getParentScope())));
            add_bb(current_bb->getExit_true());
        }
        break;

    default:
        break;
    }

    return nullptr;
}