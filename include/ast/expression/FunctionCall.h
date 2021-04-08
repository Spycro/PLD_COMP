#pragma once

#include "Expression.h"
#include <string>
#include <list>
using namespace std;

class FunctionCall : public Expression {

    public:
        FunctionCall() {type=FUNCTIONCALL;}

        FunctionCall(string symbol, list<shared_ptr<Node>> param) 
         : symbol(symbol), parameters(param) {}

        inline string& getSymbol() override { return symbol; }
        void setSymbol(std::string symbol_) override { symbol=symbol_; }

        inline list<shared_ptr<Node>> &getParameters() override { return parameters; }

        virtual std::string toString() override;

    private:
        string symbol;
        list<shared_ptr<Node>> parameters;

};
