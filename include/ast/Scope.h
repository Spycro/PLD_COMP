#pragma once
#include "../SymbolTable.h"
#include <memory>

class Scope {

    public:

    private:
        SymbolTable symbolicTable;
        std::shared_ptr<Scope> parentScope;


};