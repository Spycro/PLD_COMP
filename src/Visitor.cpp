#include "Visitor.h"
#include "ast/Node.h"
#include "ast/Function.h"
#include "ast/Return.h"
#include "ast/NullInstr.h"
#include "ast/WhileInstr.h"
#include "ast/DoWhileInstr.h"
#include "ast/IfInstr.h"
#include "ast/ForInstr.h"
#include "ast/expression/Affectation.h"
#include "ast/expression/Const.h"
#include "ast/expression/Binary.h"
#include "ast/expression/Unary.h"
#include "type/TypeUtil.h"
#include "ast/expression/FunctionCall.h"
#include "ast/expression/getCharInstr.h"
#include "ast/expression/putCharInstr.h"
#include "type/Int64.h"
#include "type/Char.h"

#include <string>

#define DEBUG

#ifdef DEBUG
  #define UNHANDLED { std::cerr << "/!\\ Unhandled operation : " << __PRETTY_FUNCTION__ << std::endl; return 0; }
  #define TRACE std::cout << "[*] visiting " << __PRETTY_FUNCTION__ << std::endl;
  #define PRINT(x) std::cout << "[*] value : " << (x) << std::endl;
  #define PRINTM(m, x) std::cout << "[*] " << (m) << " : " << (x) << std::endl;
#else
  #define UNHANDLED { std::cerr << "/!\\Unhandled operation : " << __PRETTY_FUNCTION__ << std::endl; throw; }
  #define TRACCE ;
  #define PRINT(x) ;
  #define PRINTM(m, x) ;
#endif



antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *context) {
  TRACE

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitType(ifccParser::TypeContext *context) {
  TRACE

  return visitChildren(context);
}

antlrcpp::Any Visitor::visitConstant(ifccParser::ConstantContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVarName(ifccParser::VarNameContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPutchar(ifccParser::PutcharContext *context) {
  TRACE
  // create corresponding AST node
  shared_ptr<Node> putChar = make_shared<putCharInstr>();
  

  // create links with the tree
  putChar->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(putChar); // set the new node parent

  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = putChar; //setting parent to current node before anything else
  antlrcpp::Any expression = visit(context->expression());

  parentNode = parent; //reseting parent node at the end of the call

  return antlrcpp::Any(putChar); 
}

antlrcpp::Any Visitor::visitGetchar(ifccParser::GetcharContext *context) {
  TRACE
  // create corresponding AST node
  shared_ptr<Node> getChar = make_shared<getCharInstr>();

  // create links with the tree
  getChar->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(getChar); // set the new node parent

  return antlrcpp::Any(getChar); 
}

antlrcpp::Any Visitor::visitFunctionCalling(ifccParser::FunctionCallingContext *context) {
   TRACE
  // create corresponding AST node
  shared_ptr<Node> functionCall = make_shared<FunctionCall>();
  

  // create links with the tree
  functionCall->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(functionCall); // set the new node parent

  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = functionCall; //setting parent to current node before anything else

  //antlrcpp::Any expression = visit(context->expression());

  for (auto child : context->expression()) {
    antlrcpp::Any tmp = visit(child);
    functionCall->getParameters().push_back(tmp.as<shared_ptr<Node>>());
  }

  parentNode = parent; //reseting parent node at the end of the call

  return antlrcpp::Any(functionCall); 

}

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
  // TODO : parameters
  TRACE

  // create corresponding AST node
  this->scope->addFunction("main", new VarType::Int64());
  shared_ptr<Node> mainFunct = make_shared<Function>();
  mainFunct->setSymbol("main");
  // create links with the tree
  parentNode->getChildren().push_back(mainFunct); // add the new node to it parent
  mainFunct->setParent(parentNode); // set the new node parent
  
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = mainFunct; //setting parent to current node before anything else
  visitChildren(context);
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  mainFunct->setCode(dynamic_pointer_cast<Block>(mainFunct->getChildren()[0]));

  return antlrcpp::Any(mainFunct);
}

antlrcpp::Any Visitor::visitAnyFunction(ifccParser::AnyFunctionContext *context) {
  // TODO : parameters
  TRACE

  // create corresponding AST node
  std::string functionName = context->NAME()->getSymbol()->getText();
  VarType::Type* functionType = VarType::getType(context->type()->getStart()->getText());
  this->scope->addFunction(functionName, functionType);
  shared_ptr<Node> funct = make_shared<Function>();
  funct->setSymbol(functionName);
  // create links with the tree
  parentNode->getChildren().push_back(funct); // add the new node to it parent
  funct->setParent(parentNode); // set the new node parent
  
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = funct; //setting parent to current node before anything else
  visit(context->block()); //TODO : visitchildren
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  funct->setCode(funct->getChildren()[0]);

  return antlrcpp::Any(funct);
}

antlrcpp::Any Visitor::visitFunctionParametersDeclaration(ifccParser::FunctionParametersDeclarationContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariableDeclaration(ifccParser::VariableDeclarationContext *context) {
  TRACE

  // retrieve type
  string type = context->type()->getStart()->getText();
  if (type == "int") {
    declarationType = new VarType::Int64();
  } else if (type == "char") {
    declarationType = new VarType::Char();
  }

  // visit children
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitVariableDeclarationList(ifccParser::VariableDeclarationListContext *context) {
  // TODO : tableaux
  // TODO : visite des déclarations multiples
  TRACE

  // retrieve var name
  string name = context->varName()->NAME()->getSymbol()->getText();
  PRINT(name)

  // add to scope
  scope->addVariable(name, declarationType);
  PRINT("ADDED VARIABLE")
  // if a default expression (ie. value) is given, create an affectation
  // otherwise, no AST node is needed
  if(context->expression()){
    // create corresponding AST node
    shared_ptr<Node> affectation = make_shared<Affectation>(name);

    // create links with the tree
    parentNode->getChildren().push_back(affectation); // add the new node to it parent
    affectation->setParent(parentNode); // set the new node parent

    // visit children
    shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
    parentNode = affectation; //setting parent node before anything else
    antlrcpp::Any tmp = visit(context->expression());
    parentNode = parent; //reseting parent node at the end of the call

    // set current node attributes
    shared_ptr<Node> val = tmp.as<shared_ptr<Node>>();
    PRINT(val->getType())
    affectation->setValue(move(val));

    return antlrcpp::Any(affectation);
  }
  //recursively visit declarationList
  if(context->variableDeclarationList())
    visit(context->variableDeclarationList());

  return 0;
}

antlrcpp::Any Visitor::visitNullInstr(ifccParser::NullInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> nullInstr = make_shared<NullInstr>();

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
  shared_ptr<Node> retExpr = make_shared<Return>();

  // create links with the tree
  retExpr->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(retExpr); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = retExpr; //setting parent to current node before anything else
  antlrcpp::Any expr = visit(context->expression());
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  retExpr->setValue(expr.as<shared_ptr<Node>>());
  
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
  shared_ptr<Node> block = make_shared<Block>();

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
  block->getInstructions().reserve(block->getChildren().size());
  for (shared_ptr<Node> child : block->getChildren()) {
    shared_ptr<Node> instr = dynamic_pointer_cast<Instruction>(child);
    block->getInstructions().push_back(instr);
  }

  // reseting scope
  popScope();

  return antlrcpp::Any(block);
}

antlrcpp::Any Visitor::visitWhileInstr(ifccParser::WhileInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> whileInstr = make_shared<WhileInstr>();
  
  // create links with the tree
  parentNode->getChildren().push_back(whileInstr); // add the new node to it parent
  whileInstr->setParent(parentNode); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = whileInstr; //setting parent to current node before anything else
  antlrcpp::Any test = visit(context->expression());
  antlrcpp::Any code = visit(context->instruction()); // TODO : comprendre pourquoi le retour n'est pas du bon type
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  // expression
  whileInstr->setTest(test.as<shared_ptr<Node>>());
  // code
  whileInstr->setCode(code.as<shared_ptr<Node>>());
  //whileInstr->setCode(dynamic_pointer_cast<Instruction>(whileInstr->getChildren()[1]));

  return antlrcpp::Any(whileInstr);
}

antlrcpp::Any Visitor::visitDoWhileInstr(ifccParser::DoWhileInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> doWhileInstr = make_shared<DoWhileInstr>();
  
  // create links with the tree
  parentNode->getChildren().push_back(doWhileInstr); // add the new node to it parent
  doWhileInstr->setParent(parentNode); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = doWhileInstr; //setting parent to current node before anything else
  antlrcpp::Any test = visit(context->expression());
  antlrcpp::Any code = visit(context->instruction()); // TODO : comprendre pourquoi le retour n'est pas du bon type
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  // expression
  doWhileInstr->setTest(test.as<shared_ptr<Node>>());
  // code
  doWhileInstr->setCode(code.as<shared_ptr<Node>>());
  
  return antlrcpp::Any(doWhileInstr);
}

antlrcpp::Any Visitor::visitIfInstr(ifccParser::IfInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<IfInstr> ifInstr = make_shared<IfInstr>();

  // create links with the tree
  parentNode->getChildren().push_back(ifInstr); // add the new node to it parent
  ifInstr->setParent(parentNode); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = ifInstr; //setting parent to current node before anything else
  antlrcpp::Any test = visit(context->expression());
  antlrcpp::Any ifCode = visit(context->instruction()[0]);
  antlrcpp::Any elseCode;
  if (context->instruction()[1] != nullptr) { // else code
    elseCode = visit(context->instruction()[1]); 
  } else { // no else code
    // create corresponding AST node
    shared_ptr<Node> elseCodeInstr = make_shared<NullInstr>();

    // create links with the tree
    ifInstr->getChildren().push_back(elseCodeInstr); // add the new node to it parent
    elseCodeInstr->setParent(ifInstr); // set the new node parent
    elseCode = elseCodeInstr;
  }
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  // expression
  ifInstr->setTest(ifInstr->getChildren()[0]);
  // ifcode
  ifInstr->setCode(ifInstr->getChildren()[1]);
  // elsecode
  ifInstr->setCodeElse(ifInstr->getChildren()[2]);

  return antlrcpp::Any(ifInstr);
}

antlrcpp::Any Visitor::visitForInstr(ifccParser::ForInstrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> forInstr = make_shared<ForInstr>();

  // create links with the tree
  parentNode->getChildren().push_back(forInstr); // add the new node to it parent
  forInstr->setParent(parentNode); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = forInstr; //setting parent to current node before anything else
  antlrcpp::Any expr0 = visit(context->expression()[0]);
  antlrcpp::Any expr1 = visit(context->expression()[1]);
  antlrcpp::Any expr2 = visit(context->expression()[2]);
  antlrcpp::Any code = visit(context->instruction());
  parentNode = parent; //reseting parent node at the end of the call

  // set current node attributes
  // initialisation
  forInstr->setInitialisation(expr0.as<shared_ptr<Node>>());
  // test
  forInstr->setTest(expr1.as<shared_ptr<Node>>());
  // step
  forInstr->setStep(expr2.as<shared_ptr<Node>>());
  // code
  forInstr->setCode(forInstr->getChildren()[3]);

  return antlrcpp::Any(forInstr);
}

antlrcpp::Any Visitor::visitBitwiseAnd_assign(ifccParser::BitwiseAnd_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreDecr(ifccParser::PreDecrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(PREDECR);
  // operand
  shared_ptr<Node> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitCompare(ifccParser::CompareContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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

  BinaryOperator op;
  if(context->EQUAL())
    op = EQUAL;
  else if(context->NOTEQUAL())
    op = NE;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> constant = make_shared<Const>();

  // create links with the tree
  constant->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(constant); // set the new node parent

  // set current node attributes
  int value;
  if(context->constant()->NUMBERS()){
    value = stoi(context->constant()->NUMBERS()->getSymbol()->getText());
  } else {
    value = context->constant()->CHARACTERS()->getSymbol()->getText().at(1);
  }
   

  constant->setConstValue(value);

  return antlrcpp::Any(constant);
}

antlrcpp::Any Visitor::visitMult_assign(ifccParser::Mult_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseXor(ifccParser::BitwiseXorContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  std::string opString = context->getStart()->getText();
  BinaryOperator op = BINXOR;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitAdd_assign(ifccParser::Add_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd(ifccParser::BitwiseAndContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  std::string opString = context->getStart()->getText();
  BinaryOperator op = BINAND;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitAddresOf(ifccParser::AddresOfContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostIncr(ifccParser::PostIncrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(POSTINCR);
  // operand
  shared_ptr<Node> operand = make_shared<Variable>();
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
  // TODO : tableaux
  TRACE

  // create corresponding AST node
  shared_ptr<Node> affect = make_shared<Affectation>();

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
  affect->setValue(value.as<shared_ptr<Node>>());
  affect->setSymbol(name);

  return antlrcpp::Any(affect);
}

antlrcpp::Any Visitor::visitBitwiseOr(ifccParser::BitwiseOrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  std::string opString = context->getStart()->getText();
  BinaryOperator op = BINOR;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitMultiplicationDivisionModulo(ifccParser::MultiplicationDivisionModuloContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitLesserOrGreater(ifccParser::LesserOrGreaterContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

  // create links with the tree
  binary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(binary); // set the new node parent

  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = binary; //setting parent to current node before anything else
  antlrcpp::Any op1 = visit(context->expression(0));
  antlrcpp::Any op2 = visit(context->expression(1));
  parentNode = parent; //reseting parent node at the end of the call
  BinaryOperator op;
  // set current node attributes
  // operator
  if(context->LT())
    op = LT;
  else if(context->GT())
    op = GT;
  else if(context->LTE())
    op = LTE;
  else if(context->GTE())
    op = GTE;
  PRINT(op)
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitBitwiseLeftShift_assign(ifccParser::BitwiseLeftShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalNot(ifccParser::LogicalNotContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(NOT);
  // operand
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = unary; //setting parent to current node before anything else
  antlrcpp::Any tmp = visit(context->expression()); 
  parentNode = parent; //reseting parent node at the end of the call

  shared_ptr<Node> operand = tmp.as<shared_ptr<Node>>();

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitPlusMinus(ifccParser::PlusMinusContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitFunctCall(ifccParser::FunctCallContext *context) {
  TRACE
  
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitPreIncr(ifccParser::PreIncrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  parentNode->getChildren().push_back(unary); // add the new node to it parent
  unary->setParent(parentNode); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(PREINCR);
  // operand
  shared_ptr<Node> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitSizeof(ifccParser::SizeofContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostDecr(ifccParser::PostDecrContext *context) {
  TRACE
  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  parentNode->getChildren().push_back(unary);
  unary->setParent(parentNode);

  // set current node attributes
  // operator
  unary->setOp(POSTDECR);
  // operand
  shared_ptr<Node> operand = make_shared<Variable>();
  operand->setParent(unary);
  unary->getChildren().push_back(operand);
  operand->setSymbol(context->varName()->NAME()->getSymbol()->getText());

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitLogicalAnd(ifccParser::LogicalAndContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  std::string opString = context->getStart()->getText();
  BinaryOperator op = LOGAND;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

antlrcpp::Any Visitor::visitMod_assign(ifccParser::Mod_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *context) {
  TRACE

  // visit children
  return visit(context->expression());
}

antlrcpp::Any Visitor::visitBitwiseXor_assig(ifccParser::BitwiseXor_assigContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseOr_assign(ifccParser::BitwiseOr_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitUnaryPlus(ifccParser::UnaryPlusContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(UNARYMINUS);
  // operand
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = unary; //setting parent to current node before anything else
  antlrcpp::Any tmp = visit(context->expression()); 
  parentNode = parent; //reseting parent node at the end of the call

  shared_ptr<Node> operand = tmp.as<shared_ptr<Node>>();

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitSub_assign(ifccParser::Sub_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariable(ifccParser::VariableContext *context) {
  TRACE

  // retrieve symbol
  std::string symbol = context->varName()->NAME()->getSymbol()->getText();
  PRINT(symbol)

  // create corresponding AST node
  shared_ptr<Node> variable = make_shared<Variable>(symbol);

  // create links with the tree
  parentNode->getChildren().push_back(variable); // add the new node to it parent
  variable->setParent(parentNode); // set the new node parent

  return antlrcpp::Any(variable);
}

antlrcpp::Any Visitor::visitUnaryMinus(ifccParser::UnaryMinusContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> unary = make_shared<Unary>();

  // create links with the tree
  unary->setParent(parentNode); // add the new node to it parent
  parentNode->getChildren().push_back(unary); // set the new node parent

  // set current node attributes
  // operator
  unary->setOp(UNARYMINUS);
  // operand
  // visit children
  shared_ptr<Node> parent = parentNode; //storing current parentNode into tmp var
  parentNode = unary; //setting parent to current node before anything else
  antlrcpp::Any tmp = visit(context->expression()); 
  parentNode = parent; //reseting parent node at the end of the call

  shared_ptr<Node> operand = tmp.as<shared_ptr<Node>>();

  return antlrcpp::Any(unary);
}

antlrcpp::Any Visitor::visitLogicalOr(ifccParser::LogicalOrContext *context) {
  TRACE

  // create corresponding AST node
  shared_ptr<Node> binary = make_shared<Binary>();

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
  std::string opString = context->getStart()->getText();
  BinaryOperator op = LOGOR;
  binary->setBinaryOperator(op);
  // operands
  binary->setOperand1(op1.as<shared_ptr<Node>>());
  binary->setOperand2(op2.as<shared_ptr<Node>>());

  return antlrcpp::Any(binary);
}

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
