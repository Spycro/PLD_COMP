
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx) {

  // Prologue of assembly code
  std::cout << ".global	main\n"
            << " main: \n"
            << "  pushq %rbp\n"
            << "  movq %rsp, %rbp\n";

  // Visit all declarations
  for (ifccParser::DeclarationContext *declarationCtx : ctx->declaration()) {
    this->visitDeclaration(declarationCtx);
  }

  // Final return of the main function
  this->visitRetValue(ctx->retValue());
  std::cout << "  popq %rbp\n"
            << "  ret\n";

  return 0;
}

antlrcpp::Any Visitor::visitRetValue(ifccParser::RetValueContext *ctx) {

  std::string rval;

  if (ctx->CONST()) {
    std::cout << "  movl $" << ctx->CONST()->getText() << ", %eax\n";
  } else if (ctx->VAR_NAME()) {
    int i = getVarStackIndex(ctx->VAR_NAME()->getText());
    std::cout << "  movl -" << (i + 1) * 4 << "(%rbp), %eax\n";
  }

  return 0;
}

antlrcpp::Any Visitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {

  std::string variableName = ctx->VAR_NAME()->getText();

  /*
   * Add the variable name to the list of variables.
   * Used to keep track of var index on the stack.
   *
   * TODO: keep track of variable type, visibility, etc..
   */
  this->varAddresses.emplace(variableName, stackSize);
  this->visitValue(ctx->value());
  ++stackSize;

  return 0;
}

antlrcpp::Any Visitor::visitValue(ifccParser::ValueContext *ctx) {

  if (ctx->CONST()) {

    int val = stoi(ctx->CONST()->getText());
    std::cout << "  movl $" << val << ", -" << (stackSize + 1) * 4 << "(%rbp)\n";

  } else if (ctx->VAR_NAME()) {

    int addr = getVarStackIndex(ctx->VAR_NAME()->getText());
    std::cout << "  movl -" << (addr + 1) * 4 << "(%rbp), %eax\n";
    std::cout << "  movl %eax, "
              << "-" << (stackSize + 1) * 4 << "(%rbp)\n";
  }

  return 0;
}

int Visitor::getVarStackIndex(std::string variableName) {

  auto it = varAddresses.find(variableName);

  if (it == varAddresses.end()) {
    std::cerr << "Variable not found '" << variableName << "'.";
    return -1;
  } else {
    return it->second;
  }
}