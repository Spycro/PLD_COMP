#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FunctionCall : public Expression {

    public:

        FunctionCall(string symbol, list<shared_ptr<Expression>> param) 
         : symbol(symbol), parameters(param) {}

        inline string& getSymbol() { return symbol; }
        inline list<shared_ptr<Expression>>& getParameters()  { return parameters; }

        void toString(int n);

    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};