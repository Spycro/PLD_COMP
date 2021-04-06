#pragma once
#include "../SymbolTable.h"
#include <memory>
using namespace std;

class Scope {

public:
    Scope()
        : parentScope(nullptr), symbolicTable(make_shared<SymbolTable>()) {

        }
    
    Scope(shared_ptr<SymbolTable> s, shared_ptr<Scope> p) 
        : symbolicTable(s), parentScope(p) { }
    
    Scope(shared_ptr<SymbolTable> s) : symbolicTable(s), parentScope(nullptr) { }

    inline shared_ptr<Scope> getParentScope() { return parentScope; }

    void setParentScope(shared_ptr<Scope> scope){ parentScope = scope; }

    std::shared_ptr<SymbolTableElement> getSymbol(std::string name);
    void addVariable(std::string name, Type *variableType);
    void addFunction(std::string name, Type *functionType);
    virtual std::string toString();

private:
    int getMemoryCounter64AndIncrement();
    shared_ptr<SymbolTable> symbolicTable;
    shared_ptr<Scope> parentScope;
    int memoryCounter64 =0;
};