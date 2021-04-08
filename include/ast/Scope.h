#pragma once
#include "../SymbolTable.h"
#include <memory>
using namespace std;

class Scope {

public:
    Scope()
        : parentScope(nullptr), symbolicTable(make_shared<SymbolTable>()) { }
    
    Scope(shared_ptr<SymbolTable> s)
        : symbolicTable(s), parentScope(nullptr) { }

    Scope(shared_ptr<SymbolTable> s, shared_ptr<Scope> p) 
        : symbolicTable(s), parentScope(p) { }

    int getMemoryCounter64();

    inline shared_ptr<Scope> getParentScope() { return parentScope; }
    inline void setParentScope(shared_ptr<Scope> scope){ parentScope = scope; }

    std::shared_ptr<SymbolTableElement> getSymbol(std::string name);

    shared_ptr<SymbolTableElement> addTempVariable(const VarType::Type * variableType);
    void addVariable(std::string name, const VarType::Type *variableType);
    void addArray(std::string name, const VarType::Type* arrayType, int size);
    void addFunction(std::string name, const VarType::Type *functionType);

    inline bool isFunctionBaseScope() { return functionBaseScope; }
    inline void setFunctionBaseScope(bool isFunctionBaseScope) { functionBaseScope = isFunctionBaseScope; }

    //inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }

    virtual std::string toString();

private:
    int getMemoryCounter64AndIncrement();
    shared_ptr<SymbolTable> symbolicTable;
    shared_ptr<Scope> parentScope;
    bool functionBaseScope = false;
    int memoryCounter64 =0;
};