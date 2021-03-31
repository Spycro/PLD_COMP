#pragma once

#include "Expression.h"
#include <string>
using namespace std;

class Variable : public Expression {

    public:
        void toString(int n);
        Variable(string symbol) : symbol(symbol) { }
        virtual ~Variable() { }
        
        inline string getSymbol() { return symbol; }
    private:
        string symbol;

};