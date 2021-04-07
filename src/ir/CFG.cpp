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
#include "ir/instructions/Jmp_cmp_eq.h"
#include "ir/instructions/Jmp_cmp_neq.h"
#include "ir/instructions/Cmp_eq.h"
#include "ir/instructions/Cmp_ge.h"
#include "ir/instructions/Cmp_gt.h"
#include "ir/instructions/Cmp_le.h"
#include "ir/instructions/Cmp_lt.h"
#include "ir/instructions/Cmp_neq.h"
#include "type/Int64.h"
#include "ir/ASMConstants.h"

CFG::CFG(Function* ast_, std::string label_, VarType::Type* type_, std::vector<SymbolTableElement> params_) : label(label_), type(type_){}

CFG::CFG(shared_ptr<Node> function){
    label =  function->getSymbol(); 

    shared_ptr<Node> block = function->getCode();
    shared_ptr<Scope> scope = block->getScope();


    type = scope->getSymbol(label)->getType(); 
    
    list<shared_ptr<Node>> parameters = function->getParameters();

    for(auto var : parameters){
        shared_ptr<SymbolTableElement> param = scope->getSymbol(var->getSymbol());
        myParams.push_back(param);
        incrementSpacer(param->getSize());
    }

    current_bb = std::shared_ptr<BasicBlock>(new BasicBlock(this, scope));
    bbs.push_back(current_bb);
    for(auto instr : block->getInstructions()){
        inspectInstruction(instr);
    }
    incrementSpacer(scope->getMemoryCounter64()); 
}




void CFG::add_bb(shared_ptr<BasicBlock> bb){
    current_bb = bb;
    bbs.push_back(bb);    
}
void CFG::incrementSpacer(int cnt){
    memorySpacer += cnt;
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
               << "\tsubq $" << (memorySpacer) << ", %rsp #Make room for "<< memorySpacer/8  << " variables"<< std::endl; 

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
    o << "\taddq $" << (memorySpacer) << ", %rsp #remove all local variables from stack"<< std::endl
        << "\tpopq %rbp #restore rbp from stack\n"
        << "\tret\n";
}

std::shared_ptr<SymbolTableElement> CFG::inspectInstruction(shared_ptr<Node> instr){
    std::cout<<instr->toString() << " enum: " << instr->getType()<<std::endl;
    switch (instr->getType())
    {
    case NodeType::AFFECTATION:
        {            
            shared_ptr<Node> leftValue = instr->getLValue();
            shared_ptr<Node> value = instr->getRValue();

            std::string symbol = leftValue->getSymbol();

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
            shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(leftOp->getType()->getLargestType(rightOp->getType()));
            shared_ptr<IRInstr> op;

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
            case BinaryOperator::EQUAL:
                op = shared_ptr<Cmp_eq>(new Cmp_eq(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::NE:
                op = shared_ptr<Cmp_neq>(new Cmp_neq(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::LT:
                op = shared_ptr<Cmp_lt>(new Cmp_lt(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::LTE:
                op = shared_ptr<Cmp_le>(new Cmp_le(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::GT:
                op = shared_ptr<Cmp_gt>(new Cmp_gt(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            case BinaryOperator::GTE:
                op = shared_ptr<Cmp_ge>(new Cmp_ge(current_bb.get(),*leftOp,*rightOp, *res));
                break;
            default:
                break;
            }
            current_bb->add_IRInstr(op);
            return res;
        }
        break;
    case NodeType::UNARY://todo finish
        {
            std::cout<< instr->toString()<<std::endl;
            std::cout<< instr->getUnaryOp()<<std::endl;
            std::cout<< instr->getOperand()<<std::endl;
            shared_ptr<SymbolTableElement> in= inspectInstruction(instr->getOperand());
            
            shared_ptr<IRInstr> op;
            
            std::cout<< instr->toString()<<std::endl;
            std::cout<< instr->getUnaryOp()<<std::endl;

            switch (instr->getUnaryOp())
            {
            case UnaryOperator::POSTDECR:
                {
                    shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(in->getType());
                    shared_ptr<IRInstr> copy(new Copy(current_bb.get(),*in,*res));
                    op = shared_ptr<Add>(new Add(current_bb.get(),*in,SymbolTableElement(in->getType(),"-1"), *in));
                    current_bb->add_IRInstr(copy);
                    current_bb->add_IRInstr(op);
                    return res;
                }
                break;
            case UnaryOperator::POSTINCR:
                {
                    shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(in->getType());
                    shared_ptr<IRInstr> copy(new Copy(current_bb.get(),*in,*res));
                    op = shared_ptr<Add>(new Add(current_bb.get(),*in,SymbolTableElement(in->getType(),"1"), *in));
                    current_bb->add_IRInstr(copy);
                    current_bb->add_IRInstr(op);
                    return res;
                }
                break;
            case UnaryOperator::PREDECR:
                {
                    op = shared_ptr<Add>(new Add(current_bb.get(),*in,SymbolTableElement(in->getType(),"-1"), *in));
                    current_bb->add_IRInstr(op);
                    return in;
                }
                break;
            case UnaryOperator::PREINCR:
                {
                    op = shared_ptr<Add>(new Add(current_bb.get(),*in,SymbolTableElement(in->getType(),"1"), *in));
                    current_bb->add_IRInstr(op);
                    return in;
                }
                break;
            case UnaryOperator::NOT:
                {
                    shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(in->getType());
                    op = shared_ptr<Cmp_eq>(new Cmp_eq(current_bb.get(),*in, SymbolTableElement(in->getType(),"0"), *res));
                    current_bb->add_IRInstr(op);
                    return res;
                }
                break;
            case UnaryOperator::UNARYMINUS:
                {
                    shared_ptr<SymbolTableElement> res = current_bb->getScope()->addTempVariable(in->getType());
                    op = shared_ptr<Sub>(new Sub(current_bb.get(),SymbolTableElement(in->getType(),"0"),*in, *res));
                    current_bb->add_IRInstr(op);
                    return res;
                }
                break;
            default:
                break;
            }
        }
        break;
    case NodeType::INFINSTR:
        {
            shared_ptr<SymbolTableElement> condition = inspectInstruction(instr->getTest());
            shared_ptr<Node> mainBlock = instr->getCode();
            shared_ptr<Node> elseBlock = instr->getCodeElse();

            

            //create blocks
            shared_ptr<BasicBlock> startBlock = current_bb;
            shared_ptr<BasicBlock> mainBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
            shared_ptr<BasicBlock> endBlock(new BasicBlock(this, current_bb->getScope()));
            
            //bind blocks
            startBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_true(endBlock);
            if(elseBlock->getType() == NodeType::NULLINSTR){
                startBlock->setExit_false(endBlock);
            }else if(elseBlock->getType() == NodeType::BLOCK){
                shared_ptr<BasicBlock> elseBasicBlock(new BasicBlock(this,elseBlock->getScope(),true));
                startBlock->setExit_false(elseBasicBlock);
                elseBasicBlock->setExit_true(endBlock);
            }else{
                shared_ptr<BasicBlock> elseBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
                startBlock->setExit_false(elseBasicBlock);
            }

            //instruction
            shared_ptr<Jmp_cmp_eq> jmpCmp(new Jmp_cmp_eq(startBlock.get(),*condition,SymbolTableElement(condition->getType(),"1")));
            current_bb->add_IRInstr(jmpCmp);



            //run main block
            add_bb(mainBasicBlock);
            for(auto InstrInBlock : mainBlock->getInstructions()){ 
                inspectInstruction(InstrInBlock);
            }

            //deal with else
            if(elseBlock->getType() == NodeType::BLOCK){
                add_bb(startBlock->getExit_false());
                for(auto InstrInBlock : elseBlock->getInstructions()){ 
                    inspectInstruction(InstrInBlock);
                }
            }else if(elseBlock->getType() != NodeType::NULLINSTR){
                add_bb(startBlock->getExit_false());
                inspectInstruction(elseBlock);
                current_bb->setExit_true(endBlock);
            }

            //switch to end block
            add_bb(endBlock);
        }
        break;
    case NodeType::WHILEINSTR:
        {
            shared_ptr<Node> mainBlock = instr->getCode();

            //create blocks
            shared_ptr<BasicBlock> startBlock = current_bb;
            shared_ptr<BasicBlock> mainBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
            shared_ptr<BasicBlock> endBlock(new BasicBlock(this, current_bb->getScope()));

            //bind blocks
            startBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_false(endBlock);

            

            //run main block
            //instruction
            add_bb(mainBasicBlock);
            shared_ptr<SymbolTableElement> condition = inspectInstruction(instr->getTest());
            shared_ptr<Jmp_cmp_eq> jmpCmp(new Jmp_cmp_eq(current_bb.get(),*condition,SymbolTableElement(condition->getType(),"1")));
            current_bb->add_IRInstr(jmpCmp);

            for(auto InstrInBlock : mainBlock->getInstructions()){ 
                inspectInstruction(InstrInBlock);
            }
            //switch to end block
            add_bb(endBlock);

        }
        break;
    case NodeType::DOWHILEINSTR:
        {
            shared_ptr<Node> mainBlock = instr->getCode();

            //create blocks
            shared_ptr<BasicBlock> startBlock = current_bb;
            shared_ptr<BasicBlock> mainBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
            shared_ptr<BasicBlock> endBlock(new BasicBlock(this, current_bb->getScope()));

            //bind blocks
            startBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_false(endBlock);

            

            //run main block
            //instruction
            add_bb(mainBasicBlock);

            for(auto InstrInBlock : mainBlock->getInstructions()){ 
                inspectInstruction(InstrInBlock);
            }
            shared_ptr<SymbolTableElement> condition = inspectInstruction(instr->getTest());
            shared_ptr<Jmp_cmp_eq> jmpCmp(new Jmp_cmp_eq(current_bb.get(),*condition,SymbolTableElement(condition->getType(),"1")));
            current_bb->add_IRInstr(jmpCmp);


            //switch to end block
            add_bb(endBlock);

        }
        break;
    case NodeType::FORINSTR:
        {
            shared_ptr<Node> init = instr->getInitialisation();
            shared_ptr<Node> step = instr->getStep();
            shared_ptr<Node> mainBlock = instr->getCode();

            //create blocks
            shared_ptr<BasicBlock> startBlock = current_bb;
            shared_ptr<BasicBlock> mainBasicBlock(new BasicBlock(this,mainBlock->getScope(),true));
            shared_ptr<BasicBlock> endBlock(new BasicBlock(this, current_bb->getScope()));

            //bind blocks
            startBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_true(mainBasicBlock);
            mainBasicBlock->setExit_false(endBlock);

            inspectInstruction(init);

            //run main block
            //instruction
            add_bb(mainBasicBlock);
            shared_ptr<SymbolTableElement> condition = inspectInstruction(instr->getTest());
            shared_ptr<Jmp_cmp_eq> jmpCmp(new Jmp_cmp_eq(current_bb.get(),*condition,SymbolTableElement(condition->getType(),"1")));
            current_bb->add_IRInstr(jmpCmp);
            for(auto InstrInBlock : mainBlock->getInstructions()){ 
                inspectInstruction(InstrInBlock);
            } 
            inspectInstruction(step);

            //switch to end block
            add_bb(endBlock);

        }
        break;
    case NodeType::FUNCTIONCALL:
        {
            std::string fName;
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