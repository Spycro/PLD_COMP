
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-generated/ifccVisitor.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor {
public:
  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

  virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;

  virtual antlrcpp::Any visitRetValue(ifccParser::RetValueContext *ctx) override;

  /**
   * Return the variable address, given its name.
   */
  int getVarStackIndex(std::string varName);

private:
  /**
   * Store the address of each declared variable.
   *
   * The key is the variable name, the value is the address.
   * The adress is relative to the bottom of the stack (starts at 0).
   */
  std::unordered_map<std::string, int> varAddresses;

  int stackSize = 0;
};
