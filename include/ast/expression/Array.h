#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Array : public Expression {

    public:
        void toString(int n);
        Array(string symbol, shared_ptr<Expression> position) : symbol(symbol), position(position) {}
        virtual ~Array();


        string getSymbol() { return symbol; }
        shared_ptr<Expression> getPosition() { return position; }
    private:
        string symbol;
        shared_ptr<Expression> position;

};