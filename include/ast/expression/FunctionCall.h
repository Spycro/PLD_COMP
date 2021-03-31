#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FunctionCall : public Expression {

    public:
        void toString(int n);

        FunctionCall(string symbol, list<shared_ptr<Expression>> param) 
         : symbol(symbol), parameters(param) {}
        virtual ~FunctionCall() {}

        inline string getSymbol() { return symbol; }
        inline list<shared_ptr<Expression>> getParameters()  { return parameters; }
    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};