#pragma once
#include "../SymbolTable.h"
#include <memory>

using namespace std;

class Scope {

    public:

    private:
        shared_ptr<SymbolTable> symbolicTable;
        shared_ptr<Scope> parentScope;


};