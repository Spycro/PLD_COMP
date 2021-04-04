#pragma once

#include "Expression.h"
#include <string>
using namespace std;

// TODO : ajouter type

class Variable : public Expression {

    public:
        Variable() {}

        Variable(string symbol) : symbol(symbol) { }
        
        inline string& getSymbol() { return symbol; }

        virtual std::string toString() override;

    private:
        string symbol;
};