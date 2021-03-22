#pragma once
#include "../SymbolTable.h"
#include <memory>
#include <iostream>

using namespace std;

class Scope {

    public:
        inline shared_ptr<SymbolTable> getSymbolicTable() { return symbolicTable; }
        inline shared_ptr<Scope> getParentScope() { return parentScope; }
        void toString(int n) {
            for(int i=0;i<n;i++){
                cout<<"\t";
            }
            cout<<"Scope"<<endl;
        }
    private:
        shared_ptr<SymbolTable> symbolicTable;
        shared_ptr<Scope> parentScope;


};