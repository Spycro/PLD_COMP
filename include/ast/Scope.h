#pragma once
#include "../SymbolTable.h"
#include <memory>

using namespace std;

class Scope {

    public:
        Scope(shared_ptr<SymbolTable> s, shared_ptr<Scope> p) 
            : symbolicTable(s), parentScope(p) { }
        Scope(shared_ptr<SymbolTable> s) : symbolicTable(s) { parentScope = nullptr; }

        virtual ~Scope() { }

        inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }
        inline shared_ptr<Scope> getParentScope() { return parentScope; }
        void toString(int n);
    private:
        shared_ptr<SymbolTable> symbolicTable;
        shared_ptr<Scope> parentScope;


};