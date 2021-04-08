
// Copied from a file generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "ast/Scope.h"
#include "ast/Node.h"

/**
 * This class provides an implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class Visitor : public ifccVisitor
{

public:
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) override;
    virtual antlrcpp::Any visitType(ifccParser::TypeContext *context) override;
    virtual antlrcpp::Any visitConstant(ifccParser::ConstantContext *context) override;
    virtual antlrcpp::Any visitVarName(ifccParser::VarNameContext *context) override;
    virtual antlrcpp::Any visitPutchar(ifccParser::PutcharContext *context) override;
    virtual antlrcpp::Any visitGetchar(ifccParser::GetcharContext *context) override;
    virtual antlrcpp::Any visitFunctionCalling(ifccParser::FunctionCallingContext *context) override;
    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *context) override;
    virtual antlrcpp::Any visitMainFunction(ifccParser::MainFunctionContext *context) override;
    virtual antlrcpp::Any visitAnyFunction(ifccParser::AnyFunctionContext *context) override;
    virtual antlrcpp::Any visitFunctionParametersDeclaration(ifccParser::FunctionParametersDeclarationContext *context) override;
    virtual antlrcpp::Any visitVariableDeclaration(ifccParser::VariableDeclarationContext *context) override;
    virtual antlrcpp::Any visitVariableDeclarationList(ifccParser::VariableDeclarationListContext *context) override;
    virtual antlrcpp::Any visitNullInstr(ifccParser::NullInstrContext *context) override;
    virtual antlrcpp::Any visitBreakInstr(ifccParser::BreakInstrContext *context) override;
    virtual antlrcpp::Any visitContinueInstr(ifccParser::ContinueInstrContext *context) override;
    virtual antlrcpp::Any visitReturnInstr(ifccParser::ReturnInstrContext *context) override;
    virtual antlrcpp::Any visitVarDecl(ifccParser::VarDeclContext *context) override;
    virtual antlrcpp::Any visitControlStruct(ifccParser::ControlStructContext *context) override;
    virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *context) override;
    virtual antlrcpp::Any visitInstruction(ifccParser::InstructionContext *context) override;
    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override;
    virtual antlrcpp::Any visitWhileInstr(ifccParser::WhileInstrContext *context) override;
    virtual antlrcpp::Any visitDoWhileInstr(ifccParser::DoWhileInstrContext *context) override;
    virtual antlrcpp::Any visitIfInstr(ifccParser::IfInstrContext *context) override;
    virtual antlrcpp::Any visitForInstr(ifccParser::ForInstrContext *context) override;
    virtual antlrcpp::Any visitBitwiseAnd_assign(ifccParser::BitwiseAnd_assignContext *context) override;
    virtual antlrcpp::Any visitPreDecr(ifccParser::PreDecrContext *context) override;
    virtual antlrcpp::Any visitCompare(ifccParser::CompareContext *context) override;
    virtual antlrcpp::Any visitConst(ifccParser::ConstContext *context) override;
    virtual antlrcpp::Any visitMult_assign(ifccParser::Mult_assignContext *context) override;
    virtual antlrcpp::Any visitBitwiseXor(ifccParser::BitwiseXorContext *context) override;
    virtual antlrcpp::Any visitAdd_assign(ifccParser::Add_assignContext *context) override;
    virtual antlrcpp::Any visitBitwiseAnd(ifccParser::BitwiseAndContext *context) override;
    virtual antlrcpp::Any visitAddresOf(ifccParser::AddresOfContext *context) override;
    virtual antlrcpp::Any visitPostIncr(ifccParser::PostIncrContext *context) override;
    virtual antlrcpp::Any visitBitwiseNot(ifccParser::BitwiseNotContext *context) override;
    virtual antlrcpp::Any visitBitwiseRightShift_assign(ifccParser::BitwiseRightShift_assignContext *context) override;
    virtual antlrcpp::Any visitCast(ifccParser::CastContext *context) override;
    virtual antlrcpp::Any visitDiv_assign(ifccParser::Div_assignContext *context) override;
    virtual antlrcpp::Any visitBitwiseShift(ifccParser::BitwiseShiftContext *context) override;
    virtual antlrcpp::Any visitDirect_assign(ifccParser::Direct_assignContext *context) override;
    virtual antlrcpp::Any visitBitwiseOr(ifccParser::BitwiseOrContext *context) override;
    virtual antlrcpp::Any visitMultiplicationDivisionModulo(ifccParser::MultiplicationDivisionModuloContext *context) override;
    virtual antlrcpp::Any visitLesserOrGreater(ifccParser::LesserOrGreaterContext *context) override;
    virtual antlrcpp::Any visitBitwiseLeftShift_assign(ifccParser::BitwiseLeftShift_assignContext *context) override;
    virtual antlrcpp::Any visitLogicalNot(ifccParser::LogicalNotContext *context) override;
    virtual antlrcpp::Any visitPlusMinus(ifccParser::PlusMinusContext *context) override;
    virtual antlrcpp::Any visitFunctCall(ifccParser::FunctCallContext *context) override;
    virtual antlrcpp::Any visitPreIncr(ifccParser::PreIncrContext *context) override;
    virtual antlrcpp::Any visitSizeof(ifccParser::SizeofContext *context) override;
    virtual antlrcpp::Any visitPostDecr(ifccParser::PostDecrContext *context) override;
    virtual antlrcpp::Any visitLogicalAnd(ifccParser::LogicalAndContext *context) override;
    virtual antlrcpp::Any visitMod_assign(ifccParser::Mod_assignContext *context) override;
    virtual antlrcpp::Any visitParenthesis(ifccParser::ParenthesisContext *context) override;
    virtual antlrcpp::Any visitBitwiseXor_assig(ifccParser::BitwiseXor_assigContext *context) override;
    virtual antlrcpp::Any visitBitwiseOr_assign(ifccParser::BitwiseOr_assignContext *context) override;
    virtual antlrcpp::Any visitUnaryPlus(ifccParser::UnaryPlusContext *context) override;
    virtual antlrcpp::Any visitSub_assign(ifccParser::Sub_assignContext *context) override;
    virtual antlrcpp::Any visitVariable(ifccParser::VariableContext *context) override;
    virtual antlrcpp::Any visitUnaryMinus(ifccParser::UnaryMinusContext *context) override;
    virtual antlrcpp::Any visitLogicalOr(ifccParser::LogicalOrContext *context) override;
    virtual antlrcpp::Any visitTernary(ifccParser::TernaryContext *context) override;
    virtual antlrcpp::Any visitPlusMinusSymbol(ifccParser::PlusMinusSymbolContext *context) override;

    inline shared_ptr<Node> getRootNode() { return rootNode; }
    inline shared_ptr<Scope> getScope() { return scope; }
    inline bool getErrorFlag() { return errorFlag; }
    inline string& getErrorTrace() { return errorTrace; }
private:
    shared_ptr<Scope> scope = make_shared<Scope>();

    shared_ptr<Node> rootNode = make_shared<Node>();

	shared_ptr<Node> parentNode;
    
    VarType::Type* declarationType;

    bool isBaseBlock = false;
    std::vector<antlr4::tree::TerminalNode *> varDeclNames;
    std::vector<ifccParser::TypeContext *> varDeclTypes;

    bool errorFlag = false;
    
    std::string errorTrace;

    void pushScope();
    void popScope();
    bool verifySymbolExist(std::string);
    bool verifySymbolNotExist(std::string);
    void addToErrorTrace(std::string);
    void setFail(){ errorFlag = true; }
    VarType::Type* parseType(std::string typeString);
    bool checkForReturn(shared_ptr<Node> block);
};
