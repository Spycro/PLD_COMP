#pragma once
#include "../SymbolTable.h"
#include <memory>

using namespace std;

class Scope
{

public:
    inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }
    inline shared_ptr<Scope> getParentScope() { return parentScope; }
    void addVariable(string name, Type *variableType);
    void addFunction(string name, Type *functionType);
    virtual std::string toString();

private:
    shared_ptr<SymbolTable> symbolicTable;
    shared_ptr<Scope> parentScope;
};