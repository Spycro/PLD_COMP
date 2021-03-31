#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Array : public Expression {

    public:
        Array(string symbol, shared_ptr<Expression> position) : symbol(symbol), position(position) {}


        inline string& getSymbol() { return symbol; }
        inline shared_ptr<Expression> getPosition() { return position; }
        void toString(int n);

    private:
        string symbol;
        shared_ptr<Expression> position;

};