#pragma once

#include "Expression.h"
#include <string>
using namespace std;

class Variable : public Expression {

    public:
        Variable(string symbol) : symbol(symbol) { }
        
        inline string& getSymbol() { return symbol; }

        void toString(int n);

    private:
        string symbol;

};