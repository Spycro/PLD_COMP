#include "Visitor.h"
#include "ast/Node.h"
#include "ast/Function.h"

#define UNHANDLED { return 0 ; }
//define UNHANDLED { throw "Unhandled operation (__PRETTY_FUNCTION__)"; }

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *context) {
  return visitProg(context);
}

antlrcpp::Any Visitor::visitVarName(ifccParser::VarNameContext *context) UNHANDLED

antlrcpp::Any Visitor::visitFunctionCall(ifccParser::FunctionCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *context) {
  parentNode = rootNode;
  return visitChildren(context);
}

antlrcpp::Any Visitor::visitMainFunction(ifccParser::MainFunctionContext *context) {
  scope.addFunction("main", new Int());

  shared_ptr<Function> mainFunct = make_shared<Function>();
  parentNode->children.insert(mainFunct);
  mainFunct->parent = parentNode;
  
  shared_ptr<Node> parent = parentNode;
  parentNode = mainFunct;
  antlrcpp::Any ret = visitChildren(context);
  parentNode = parent;

  mainFunct->code = children[0];

  return ret;
}

antlrcpp::Any Visitor::visitAnyFunction(ifccParser::AnyFunctionContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariableDeclaration(ifccParser::VariableDeclarationContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariableDeclarationList(ifccParser::VariableDeclarationListContext *context) UNHANDLED

antlrcpp::Any Visitor::visitNullInstr(ifccParser::NullInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBreakInstr(ifccParser::BreakInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitContinueInstr(ifccParser::ContinueInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitReturnInstr(ifccParser::ReturnInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *context) UNHANDLED

antlrcpp::Any Visitor::visitControlStruct(ifccParser::ControlStructContext *context) UNHANDLED

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *context) UNHANDLED

antlrcpp::Any Visitor::visitInstruction(ifccParser::InstructionContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context) {
  shared_ptr<Block> block = make_shared<Block>();
  parentNode->children.insert(block);
  block->parent = parentNode;

  shared_ptr<Node> parent = parentNode;
  parentNode = block;
  antlrcpp::Any ret = visitChildren(context);
  parentNode = parent;
  
  // TODO : remplir l'attribut "instructions" de block

  return ret;
}

antlrcpp::Any Visitor::visitWhileInstr(ifccParser::WhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitDoWhileInstr(ifccParser::DoWhileInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitIfInstr(ifccParser::IfInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitForInstr(ifccParser::ForInstrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseAnd_assign(ifccParser::BitwiseAnd_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreDecr(ifccParser::PreDecrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitCompare(ifccParser::CompareContext *context) UNHANDLED

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context) UNHANDLED

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

antlrcpp::Any Visitor::visitDirect_assign(ifccParser::Direct_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseOr(ifccParser::BitwiseOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMultiplicationDivisionModulo(ifccParser::MultiplicationDivisionModuloContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLesserOrGreater(ifccParser::LesserOrGreaterContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseLeftShift_assign(ifccParser::BitwiseLeftShift_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalNot(ifccParser::LogicalNotContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPlusMinus(ifccParser::PlusMinusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitFunctCall(ifccParser::FunctCallContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPreIncr(ifccParser::PreIncrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitSizeof(ifccParser::SizeofContext *context) UNHANDLED

antlrcpp::Any Visitor::visitPostDecr(ifccParser::PostDecrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalAnd(ifccParser::LogicalAndContext *context) UNHANDLED

antlrcpp::Any Visitor::visitMod_assign(ifccParser::Mod_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseXor_assig(ifccParser::BitwiseXor_assigContext *context) UNHANDLED

antlrcpp::Any Visitor::visitBitwiseOr_assign(ifccParser::BitwiseOr_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitComma(ifccParser::CommaContext *context) UNHANDLED

antlrcpp::Any Visitor::visitUnaryPlus(ifccParser::UnaryPlusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitSub_assign(ifccParser::Sub_assignContext *context) UNHANDLED

antlrcpp::Any Visitor::visitVariable(ifccParser::VariableContext *context) UNHANDLED

antlrcpp::Any Visitor::visitUnaryMinus(ifccParser::UnaryMinusContext *context) UNHANDLED

antlrcpp::Any Visitor::visitLogicalOr(ifccParser::LogicalOrContext *context) UNHANDLED

antlrcpp::Any Visitor::visitTernary(ifccParser::TernaryContext *context) UNHANDLED
