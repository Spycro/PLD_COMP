#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Visitor.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-runtime.h"
#include "ir/IR.h"

//#define DEBUG

using namespace antlr4;
using namespace std;

void PrintAst(shared_ptr<Node> node, int count);
void PrintScope(shared_ptr<Scope>, int count);

class ErrorListener : public BaseErrorListener {
public:
    ErrorListener() { error = false; }
    bool hasError() { return error; }
    virtual void syntaxError(Recognizer *recognizer, Token *offendingSymbol,
                            size_t line, size_t charPositionInLine,
                            const std::string &msg, std::exception_ptr e) {
        cerr << "[!] Syntax error on line " << line << ", column " << charPositionInLine << ": " << msg << endl;
        error = true;
    }

protected:
    bool error;
};

int main(int argn, const char **argv) {

    stringstream in;

    if (argn == 2) {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }

    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);

    ErrorListener errorListener;

    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);

    CommonTokenStream tokens(&lexer);

    tokens.fill();

    if (errorListener.hasError())
        return 1;

    ifccParser parser(&tokens);

    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    tree::ParseTree *tree = parser.axiom();
    
    if (errorListener.hasError())
        return 1;

    Visitor visitor;
    visitor.visit(tree);

    shared_ptr<Node> rootNode = visitor.getRootNode();

    #ifdef DEBUG
    PrintAst(rootNode, 0);
    #endif
    
    if(visitor.getErrorFlag()){
        std::cerr << visitor.getErrorTrace() << std::endl;
        return 1;
    }

    //IR
    IR myIR(rootNode);
    

    return 0;
}


void PrintAst(shared_ptr<Node> node, int count){
  std::cout << std::string(count, ' ') << node->toString() << std::endl; 

  for(auto childNode : node->getChildren()){
    PrintAst(childNode, count+1);
  }
}

void PrintScope(shared_ptr<Scope> scope, int count){
  cout << "Scope at level : " << count << endl;
}