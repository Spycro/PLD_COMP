#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FunctionCall : public Expression {

    public:

        //Bad constructor, need to rewrite the param list
        FunctionCall(string symbol, list<shared_ptr<Expression>> param) 
         : symbol(symbol), parameters(param) {}
        virtual ~FunctionCall() {}

        string getSymbol() { return symbol; }
        list<shared_ptr<Expression>> getParameters()  { return parameters; }
    private:
        string symbol;
        list<shared_ptr<Expression>> parameters;

};