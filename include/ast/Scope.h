#pragma once
#include "../SymbolTable.h"
#include <memory>

using namespace std;

class Scope {

    public:
        inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }
        inline shared_ptr<Scope> getParentScope() { return parentScope; }
        void toString(int n);
    private:
        shared_ptr<SymbolTable> symbolicTable;
        shared_ptr<Scope> parentScope;


};