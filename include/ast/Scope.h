#pragma once
#include "../SymbolTable.h"
#include <memory>
#include <iostream> //Debuggin utilities
using namespace std;

class Scope {

public:
    Scope()
        : parentScope(nullptr), symbolicTable(make_shared<SymbolTable>()) {

        }
    
    Scope(shared_ptr<SymbolTable> s, shared_ptr<Scope> p) 
        : symbolicTable(s), parentScope(p) { }
    
    Scope(shared_ptr<SymbolTable> s) : symbolicTable(s), parentScope(nullptr) { }

    inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }
    inline shared_ptr<Scope> getParentScope() { return parentScope; }

    void setParentScope(shared_ptr<Scope> scope){ parentScope = scope; }

    void addVariable(string name, Type *variableType);
    void addFunction(string name, Type *functionType);
    virtual std::string toString();

private:
    shared_ptr<SymbolTable> symbolicTable;
    shared_ptr<Scope> parentScope;
};