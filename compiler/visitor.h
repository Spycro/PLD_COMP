
// Copied from a file generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccVisitor {
public:
	virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override; //no comment
	virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override; //base program (main in this case), calls children
	virtual antlrcpp::Any visitLine(ifccParser::LineContext *ctx) override; //a basic line, either a declaration or affectation

	virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override; //A declaration
	virtual antlrcpp::Any visitSimpleDeclaration(ifccParser::SimpleDeclarationContext *ctx) override; //A declaration without affectation
	virtual antlrcpp::Any visitAssignDeclaration(ifccParser::AssignDeclarationContext *ctx) override; //A declaration with affectation

	virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override;//An affectation

	virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;//retrieve const value
	virtual antlrcpp::Any visitVariable(ifccParser::VariableContext *ctx) override;//retrieve variable

	//expression visitors
	virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override;
	virtual antlrcpp::Any visitDiv(ifccParser::DivContext *ctx) override;
	virtual antlrcpp::Any visitAdd(ifccParser::AddContext *ctx) override;
	virtual antlrcpp::Any visitSub(ifccParser::SubContext *ctx) override;
	virtual antlrcpp::Any visitMinus(ifccParser::MinusContext *ctx) override;
	virtual antlrcpp::Any visitExpressionValue(ifccParser::ExpressionValueContext *ctx) override;
	virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;
	virtual antlrcpp::Any visitAffectationValue(ifccParser::AffectationValueContext *ctx) override;

private:
	std::unordered_map<std::string,std::string> symbols; //all symbols
	std::unordered_set<std::string> symbolsNotUsed; //Symbols that have not been used yet
	int stackPointer = 0; // ehm, the stack pointer? what else do you want explained?

	std::string addVariable(); //Private function to add a temp variable to the symbols

	//A private function to add a variable with a name. If temp set to true then we know it will be used
	std::string addVariable(std::string name, bool temp = false);
	std::string getVariable(std::string name);//A private function used to retrieve a variable from the symbols
};

