#include "Visitor.h"
#include "ast/Node.h"
#include "ast/Function.h"
#include "ast/Return.h"
#include "ast/NullInstr.h"
#include "ast/expression/Affectation.h"
#include "ast/expression/Const.h"
#include "ast/expression/Binary.h"
#include "ast/expression/Unary.h"
#include "type/Int.h"
#include "type/Char.h"



#define DEBUG

#ifdef DEBUG
  #define UNHANDLED { std::cout << "/!\\ unhandled function : " << __PRETTY_FUNCTION__ << std::endl; return 0 ; }
  #define TRACE std::cout << "[*] visiting " << __PRETTY_FUNCTION__ << std::endl;
  #define PRINT(x) std::cout << "[*] value : " << x << std::endl;
  #define PRINTM(m, x) std::cout << "[*] " << m << " : " << x << std::endl;
#else
  #define UNHANDLED { throw "Unhandled operation (__PRETTY_FUNCTION__)"; }
  #define TRACCE ;
  #define PRINT(x) ;
  #define PRINTM(m, x) ;
#endif



antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *context) {
  TRACE

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitVarName(ifccParser::VarNameContext *context) UNHANDLED

antlrcpp::Any Visitor::visitFunctionCall(ifccParser::FunctionCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *context) {
  TRACE
  PRINTM("Global scope - #variable : ", context->variableDeclaration().size())
  PRINTM("Global scope - #function : ", context->functionDeclaration().size())

  // base node
  parentNode = rootNode;

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitMainFunction(ifccParser::MainFunctionContext *context) {
  TRACE

  // create corresponding AST node
  this->scope->addFunction("main", new Int());
  shared_ptr<Function> mainFunct = make_shared<Function>();
  
  // create links with the tree
  parentNode->getChildren().push_back(mainFunct); // add the new node to it parent
  mainFunct->setParent(parentNode); // set the new node parent
  
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = mainFunct; //setting parent to current node before anything else
  antlrcpp::Any ret = visitChildren(context);
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  mainFunct->setCode(dynamic_pointer_cast<Block>(mainFunct->getChildren()[0]));

  return ret;
}

antlrcpp::Any Visitor::visitAnyFunction(ifccParser::AnyFunctionContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariableDeclaration(ifccParser::VariableDeclarationContext *context) {
  TRACE

  // retrieve type
  string type = context->TYPE()->getSymbol()->getText();
  if (type == "int") {
    declarationType = new Int();
  } else if (type == "char") {
    declarationType = new Char();
  }

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitVariableDeclarationList(ifccParser::VariableDeclarationListContext *context) {
  // TODO : scope du bloc / fait ??
  // TODO : tableaux
  // TODO : affectation au moment de la declaration
  // TODO : visite des déclarations multiples
  TRACE

  // retrieve var name
  string name = context->varName()->NAME()->getSymbol()->getText();
  PRINT(name)

  // add to scope
  scope->addVariable(name, declarationType);

  // if a default expression (ie. value) is given, create an affectation
  // otherwise, no AST node is needed
  if(context->expression()){
    // create corresponding AST node
    shared_ptr<Affectation> affectation = make_shared<Affectation>(name);

    // create links with the tree
    parentNode->getChildren().push_back(affectation); // add the new node to it parent
    affectation->setParent(parentNode); // set the new node parent

    // visit children
    shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
    parentNode = affectation; //setting parent node before anything else
    antlrcpp::Any tmp = visit(context->expression());
    parentNode = parent; //reseting parent node at the end of the call

    // set current node attributes
    shared_ptr<Expression> val = tmp.as<shared_ptr<Expression>>();
    affectation->setValue(move(val));
    parentNode->getChildren().push_back(affectation);

    return antlrcpp::Any(affectation);
  }

  return 0;
}

antlrcpp::Any Visitor::visitNullInstr(ifccParser::NullInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<NullInstr> nullInstr = make_shared<NullInstr>();

  // create links with the tree
  nullInstr->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(nullInstr); // set the new node parent

  return antlrcpp::Any(nullInstr);
}

antlrcpp::Any Visitor::visitBreakInstr(ifccParser::BreakInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitContinueInstr(ifccParser::ContinueInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitReturnInstr(ifccParser::ReturnInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Return> retExpr = make_shared<Return>();

  // create links with the tree
  retExpr->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(retExpr); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = retExpr; //setting parent to current node before anything else
  antlrcpp::Any expr = visit(context->expression());
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  //retExpr->setValue(dynamic_pointer_cast<Expression>(retExpr->getChildren()[0]));
  retExpr->setValue(expr.as<shared_ptr<Expression>>());
  
  return antlrcpp::Any(retExpr);
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *context) {
  TRACE

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitControlStruct(ifccParser::ControlStructContext *context) {
  TRACE

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *context) {
  TRACE

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitInstruction(ifccParser::InstructionContext *context) {
  TRACE
  
  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context) {
  TRACE

  // updating scope 
  pushScope();

  // create corresponding AST node
  shared_ptr<Block> block = make_shared<Block>();

  // create links with the tree
  block->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(block); // set the new node parent
  block->setScope(scope); // setting scope to new scope

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = block; //setting parent to current node before anything else
  visitChildren(context);
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  for (shared_ptr<Node> child : block->getChildren()) {
    shared_ptr<Instruction> instr = dynamic_pointer_cast<Instruction>(child);
    block->getInstructions().push_back(instr);
  }

  // reseting scope
  popScope();

  return antlrcpp::Any(block);
}

antlrcpp::Any Visitor::visitWhileInstr(ifccParser::WhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDoWhileInstr(ifccParser::DoWhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitIfInstr(ifccParser::IfInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitForInstr(ifccParser::ForInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd_assign(ifccParser::BitwiseAnd_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreDecr(ifccParser::PreDecrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(PREDECR);
  // operand
  shared_ptr<Expression> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitCompare(ifccParser::CompareContext *context) UNHANDLED

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> constant = make_shared<Const>();

  // create links with the tree
  constant->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(constant); // set the new node parent

  // set current node attributes
  int value = stoi(context->CONST()->getSymbol()->getText());
  constant->setValue(value);

  return antlrcpp::Any(constant);
}

antlrcpp::Any Visitor::visitMult_assign(ifccParser::Mult_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseXor(ifccParser::BitwiseXorContext *context) UNHANDLED

antlrcpp::Any Visitor::visitAdd_assign(ifccParser::Add_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd(ifccParser::BitwiseAndContext *context) UNHANDLED

antlrcpp::Any Visitor::visitAddresOf(ifccParser::AddresOfContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostIncr(ifccParser::PostIncrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(POSTINCR);
  // operand
  shared_ptr<Expression> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitBitwiseNot(ifccParser::BitwiseNotContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseRightShift_assign(ifccParser::BitwiseRightShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitCast(ifccParser::CastContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDiv_assign(ifccParser::Div_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseShift(ifccParser::BitwiseShiftContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDirect_assign(ifccParser::Direct_assignContext *context) {
  // TODO : vérifier type
  // TODO : tableaux
  // TODO : vérifier que ça existe ?
  // TODO : trouver la bonne table de symboles
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> affect = make_shared<Affectation>();

  // create links with the tree
  affect->getParent() = parentNode; // add the new node to it parent
  parentNode->getChildren().push_back(affect); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = affect; //setting parent to current node before anything else
  antlrcpp::Any value = visit(context->expression());
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  string name = context->varName()->NAME()->getText();
  affect->setValue(value.as<shared_ptr<Expression>>());

  return antlrcpp::Any(affect);

  // TODO : supprimer ? 
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
}

antlrcpp::Any Visitor::visitBitwiseOr(ifccParser::BitwiseOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMultiplicationDivisionModulo(ifccParser::MultiplicationDivisionModuloContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> binary = make_shared<Binary>();

  // create links with the tree
  binary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(binary); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = binary; //setting parent to current node before anything else
  antlrcpp::Any op1 = visit(context->expression(0));
  antlrcpp::Any op2 = visit(context->expression(1));
  parentNode = parent; //reseting parent node at the end of the call


  // set current node attributes
  // operator
  std::string opString = context->MULTDIVMOD()->getSymbol()->getText();
  BinaryOperator op;
  if(opString == "*")
    op = MULT;
  else if(opString == "/")
    op = DIV;
  else if(opString == "%")
    op = MOD;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Expression>>());
  binary->setOperand2(op2.as<shared_ptr<Expression>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitLesserOrGreater(ifccParser::LesserOrGreaterContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseLeftShift_assign(ifccParser::BitwiseLeftShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalNot(ifccParser::LogicalNotContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPlusMinus(ifccParser::PlusMinusContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> binary = make_shared<Binary>();

  // create links with the tree
  binary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(binary); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = binary; //setting parent to current node before anything else
  antlrcpp::Any op1 = visit(context->expression(0));
  antlrcpp::Any op2 = visit(context->expression(1));
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  // operator
  std::string opString = context->plusMinusSymbol()->getStart()->getText();
  BinaryOperator op;
  if(opString == "+")
    op = PLUS;
  else if(opString == "-")
    op = MINUS;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Expression>>());
  binary->setOperand2(op2.as<shared_ptr<Expression>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitFunctCall(ifccParser::FunctCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreIncr(ifccParser::PreIncrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Expression> unary = make_shared<Unary>();

  // create links with the tree
  parentNode->getChildren().push_back(unary); // add the new node to it parent
  unary->setParent(parentNode); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(PREINCR);
  // operand
  shared_ptr<Expression> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitSizeof(ifccParser::SizeofContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostDecr(ifccParser::PostDecrContext *context) {
  TRACE
  // create corresponding AST node
  shared_ptr<Expression> unary = make_shared<Unary>();

  // create links with the tree
  parentNode->getChildren().push_back(unary);
  unary->setParent(parentNode);

  // set current node attributes
  // operator
  unary->setOp(POSTDECR);
  // operand
  shared_ptr<Expression> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitLogicalAnd(ifccParser::LogicalAndContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMod_assign(ifccParser::Mod_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *context) {
  TRACE

  // visit children
  return visit(context->expression());
}

antlrcpp::Any Visitor::visitBitwiseXor_assig(ifccParser::BitwiseXor_assigContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseOr_assign(ifccParser::BitwiseOr_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitComma(ifccParser::CommaContext *context) UNHANDLED

antlrcpp::Any Visitor::visitUnaryPlus(ifccParser::UnaryPlusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitSub_assign(ifccParser::Sub_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariable(ifccParser::VariableContext *context) {
  TRACE

  // retrieve symbol
  std::string symbol = context->varName()->NAME()->getSymbol()->getText();
  PRINT(symbol)

  // create corresponding AST node
  shared_ptr<Expression> variable = make_shared<Variable>(symbol);

  // create links with the tree
  parentNode->getChildren().push_back(variable); // add the new node to it parent
  variable->setParent(parentNode); // set the new node parent

  return antlrcpp::Any(variable);
}

antlrcpp::Any Visitor::visitUnaryMinus(ifccParser::UnaryMinusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalOr(ifccParser::LogicalOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitTernary(ifccParser::TernaryContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPlusMinusSymbol(ifccParser::PlusMinusSymbolContext *context) UNHANDLED

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
