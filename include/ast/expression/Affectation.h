#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression {

    public:
        Affectation(string symbol, shared_ptr<Expression> value) : symbol(symbol), value(value) {}
        
        inline string& getSymbol() { return symbol; }
        inline shared_ptr<Expression> getValue() { return value; }
        void toString(int n);

    private:

        string symbol;
        shared_ptr<Expression> value;

};