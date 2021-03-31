#include <iostream>
#include <sstream>

#include "Visitor.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-runtime.h"

using namespace antlr4;
using namespace std;

class MyErrorListener : public BaseErrorListener
{
public:
    MyErrorListener() { error = false; }
    bool Error() { return error; }
    virtual void syntaxError(Recognizer *recognizer, Token *offendingSymbol,
                             size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e)
    {
        cout << "Error on position " << line << ":" << charPositionInLine << endl;
        error = true;
    }

protected:
    bool error;
};

void printASTRecursive(shared_ptr<Node> node, int n, ostream &o)
{
    o << std::string(n, '\t') << "└";
    o << node->toString() << endl;

    for (shared_ptr<Node> child : node->getChildren())
    {
        printASTRecursive(child, n + 1, o);
    }
}

int main(int argn, const char **argv)
{
    stringstream in;
    if (argn == 2)
    {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }
    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    ifccParser parser(&tokens);

    MyErrorListener errorlistener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorlistener);

    tree::ParseTree *tree = parser.axiom();
    if (errorlistener.Error())
        return 1;

    Visitor visitor;
    visitor.visit(tree);

    printASTRecursive(visitor.getRootNode(), 0, cout);

    return 0;
}
