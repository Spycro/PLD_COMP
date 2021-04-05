#include "Visitor.h"
#include "ast/Node.h"
#include "ast/Function.h"
#include "ast/Return.h"
#include "ast/expression/Affectation.h"
#include "ast/expression/Const.h"
#include "ast/expression/Binary.h"
#include "type/Int.h"
#include "type/Char.h"
#include <iostream>

#define UNHANDLED { return 0 ; }
//define UNHANDLED { throw "Unhandled operation (__PRETTY_FUNCTION__)"; }

#define TRACE std::cout << "[*] visiting " << __PRETTY_FUNCTION__ << std::endl;
#define PRINT(x) std::cout << "[*] value : " << x << std::endl; 

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *context) {
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitVarName(ifccParser::VarNameContext *context) UNHANDLED

antlrcpp::Any Visitor::visitFunctionCall(ifccParser::FunctionCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *context) {
  TRACE  
  std::cout<<"var:"<<context->variableDeclaration().size()<<std::endl;
  std::cout<<"fx:"<<context->functionDeclaration().size()<<std::endl;

  parentNode = rootNode;
  
  // TODO : decla variables
/*
  for (auto fx : context->functionDeclaration()) {
    std::cout<<"for"<<std::endl;
    visit(fx);
  }*/

  return visitChildren(context);
}

antlrcpp::Any Visitor::visitMainFunction(ifccParser::MainFunctionContext *context) {
  TRACE
  this->scope->addFunction("main", new Int());
  
  shared_ptr<Function> mainFunct = make_shared<Function>();
  parentNode->getChildren().push_back(mainFunct);
  mainFunct->setParent(parentNode);
  
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = mainFunct; //setting parent node before anything else
  antlrcpp::Any ret = visitChildren(context);
  parentNode = parent; //reseting parent node at the end of the call

  mainFunct->setCode(dynamic_pointer_cast<Block>(mainFunct->getChildren()[0]));

  return ret;
}

antlrcpp::Any Visitor::visitAnyFunction(ifccParser::AnyFunctionContext *context) {
  TRACE
  return 0;
}

antlrcpp::Any Visitor::visitVariableDeclaration(ifccParser::VariableDeclarationContext *context) {
  TRACE
  string type = context->TYPE()->getSymbol()->getText();

  if (type == "int") {
    declarationType = new Int();
  } else if (type == "char") {
    declarationType = new Char();
  }

  return visitChildren(context);
}

antlrcpp::Any Visitor::visitVariableDeclarationList(ifccParser::VariableDeclarationListContext *context) {
  // TODO : scope du bloc
  // TODO : tableaux
  // TODO : affectation au moment de la declaration
  // TODO : visite des déclarations multiples
  TRACE

  string name = context->varName()->NAME()->getSymbol()->getText();
  PRINT(name)
  scope->addVariable(name, declarationType);
  if(context->expression()){
    shared_ptr<Affectation> affectation = make_shared<Affectation>(name);

    shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
    parentNode = affectation; //setting parent node before anything else
    antlrcpp::Any tmp = visit(context->expression());
    parentNode = parent; //reseting parent node at the end of the call

    shared_ptr<Expression> val = tmp.as<shared_ptr<Expression>>();
    affectation->setValue(move(val));
    parentNode->getChildren().push_back(affectation);

  }

  return 0;
}

antlrcpp::Any Visitor::visitNullInstr(ifccParser::NullInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBreakInstr(ifccParser::BreakInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitContinueInstr(ifccParser::ContinueInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitReturnInstr(ifccParser::ReturnInstrContext *context) {
  TRACE
  shared_ptr<Return> retExpr = make_shared<Return>();
  retExpr->setParent(parentNode);
  parentNode->getChildren().push_back(retExpr);

  shared_ptr<Node> parent = parentNode;
  parentNode = retExpr;
  antlrcpp::Any ret = visit(context->expression());
  parentNode = parent;

  retExpr->setValue(dynamic_pointer_cast<Expression>(retExpr->getChildren()[0]));

  return ret;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *context) {
  TRACE
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitControlStruct(ifccParser::ControlStructContext *context) UNHANDLED

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *context) {
  TRACE
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitInstruction(ifccParser::InstructionContext *context) {
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context) {
  TRACE
  pushScope();
  shared_ptr<Block> block = make_shared<Block>();
  block->setParent(parentNode);
  parentNode->getChildren().push_back(block);
    
  block->setScope(scope);

  shared_ptr<Node> parent = parentNode;
  parentNode = block;
  antlrcpp::Any ret = visitChildren(context);
  parentNode = parent;

  for (shared_ptr<Node> child : block->getChildren()) {
    shared_ptr<Instruction> instr = dynamic_pointer_cast<Instruction>(child);
    block->getInstructions().push_back(instr);
  }
  popScope();
  return ret;
}

antlrcpp::Any Visitor::visitWhileInstr(ifccParser::WhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDoWhileInstr(ifccParser::DoWhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitIfInstr(ifccParser::IfInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitForInstr(ifccParser::ForInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd_assign(ifccParser::BitwiseAnd_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreDecr(ifccParser::PreDecrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitCompare(ifccParser::CompareContext *context) UNHANDLED

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context) {
  TRACE
  shared_ptr<Expression> constant = make_shared<Const>();
  constant->setParent(parentNode);
  parentNode->getChildren().push_back(constant);

  int value = stoi(context->CONST()->getSymbol()->getText());

  constant->setValue(value);

  return antlrcpp::Any(constant);
}

antlrcpp::Any Visitor::visitMult_assign(ifccParser::Mult_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseXor(ifccParser::BitwiseXorContext *context) UNHANDLED

antlrcpp::Any Visitor::visitAdd_assign(ifccParser::Add_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd(ifccParser::BitwiseAndContext *context) UNHANDLED

antlrcpp::Any Visitor::visitAddresOf(ifccParser::AddresOfContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostIncr(ifccParser::PostIncrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseNot(ifccParser::BitwiseNotContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseRightShift_assign(ifccParser::BitwiseRightShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitCast(ifccParser::CastContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDiv_assign(ifccParser::Div_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseShift(ifccParser::BitwiseShiftContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDirect_assign(ifccParser::Direct_assignContext *context) {

  /*
  shared_ptr<Affectation> affectation = make_shared<Affectation>(name);

    shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
    parentNode = affectation; //setting parent node before anything else
    antlrcpp::Any tmp = visit(context->expression());
    parentNode = parent; //reseting parent node at the end of the call

    shared_ptr<Expression> val = tmp.as<shared_ptr<Expression>>();
    affectation->setValue(move(val));
    parentNode->getChildren().push_back(affectation);
  */


  TRACE
  shared_ptr<Expression> affect = make_shared<Affectation>();
  affect->getParent() = parentNode;
  parentNode->getChildren().push_back(affect);

  // TODO : vérifier type
  // TODO : tableaux
  // TODO : vérifier que ça existe
  // TODO : trouver la bonne table de symboles

  string name = context->varName()->NAME()->getText();
  
  shared_ptr<Node> parent = parentNode;
  parentNode = affect;
  antlrcpp::Any ret = visit(context->expression());
  parentNode = parent;

  affect->setValue(ret.as<shared_ptr<Expression>>());

  return antlrcpp::Any(affect);
}

antlrcpp::Any Visitor::visitBitwiseOr(ifccParser::BitwiseOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMultiplicationDivisionModulo(ifccParser::MultiplicationDivisionModuloContext *context) {
  TRACE
  shared_ptr<Expression> binary = make_shared<Binary>();
  binary->setParent(parentNode);
  parentNode->getChildren().push_back(binary);
  std::string opString = context->MULTDIVMOD()->getSymbol()->getText();
  BinaryOperator op;
  if(opString == "*")
    op = MULT;
  else if(opString == "/")
    op = DIV;
  else if(opString == "%")
    op = MOD;
  
  binary->setBinaryOperator(op);

  shared_ptr<Node> tmp = parentNode;
  parentNode = binary;

  antlrcpp::Any op1 = visit(context->expression(0));
  antlrcpp::Any op2 = visit(context->expression(1));
  parentNode = tmp;
  binary->setOperand1(op1.as<shared_ptr<Expression>>());
  binary->setOperand2(op2.as<shared_ptr<Expression>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitLesserOrGreater(ifccParser::LesserOrGreaterContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseLeftShift_assign(ifccParser::BitwiseLeftShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalNot(ifccParser::LogicalNotContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPlusMinus(ifccParser::PlusMinusContext *context) {
  TRACE
  shared_ptr<Expression> binary = make_shared<Binary>();
  binary->setParent(parentNode);
  parentNode->getChildren().push_back(binary);
  std::string opString = context->plusMinusSymbol()->getStart()->getText();
  BinaryOperator op;
  if(opString == "+")
    op = PLUS;
  else if(opString == "-")
    op = MINUS;
  
  binary->setBinaryOperator(op);

  shared_ptr<Node> tmp = parentNode;
  parentNode = binary;

  antlrcpp::Any op1 = visit(context->expression(0));
  antlrcpp::Any op2 = visit(context->expression(1));
  parentNode = tmp;
  binary->setOperand1(op1.as<shared_ptr<Expression>>());
  binary->setOperand2(op2.as<shared_ptr<Expression>>());

  return antlrcpp::Any(binary);

}

antlrcpp::Any Visitor::visitFunctCall(ifccParser::FunctCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreIncr(ifccParser::PreIncrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitSizeof(ifccParser::SizeofContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostDecr(ifccParser::PostDecrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalAnd(ifccParser::LogicalAndContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMod_assign(ifccParser::Mod_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *context) {
  TRACE
  return visit(context->expression());
}

antlrcpp::Any Visitor::visitBitwiseXor_assig(ifccParser::BitwiseXor_assigContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseOr_assign(ifccParser::BitwiseOr_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitComma(ifccParser::CommaContext *context) UNHANDLED

antlrcpp::Any Visitor::visitUnaryPlus(ifccParser::UnaryPlusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitSub_assign(ifccParser::Sub_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariable(ifccParser::VariableContext *context) {
  TRACE
  std::string symbol = context->varName()->NAME()->getSymbol()->getText();
  PRINT(symbol)
  shared_ptr<Expression> tmp = make_shared<Variable>(symbol);
  parentNode->getChildren().push_back(tmp);


  return antlrcpp::Any(tmp);
}

antlrcpp::Any Visitor::visitUnaryMinus(ifccParser::UnaryMinusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalOr(ifccParser::LogicalOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitTernary(ifccParser::TernaryContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPlusMinusSymbol(ifccParser::PlusMinusSymbolContext *context) UNHANDLED;


void Visitor::pushScope() {
  TRACE
  shared_ptr<Scope> newScope = make_shared<Scope>();
  newScope->setParentScope(scope);
  scope = newScope;
}

void Visitor::popScope() {
  TRACE
  scope = scope->getParentScope();
}
