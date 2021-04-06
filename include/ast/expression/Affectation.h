#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression
{

    public:
        Affectation()
            : value(nullptr) {type=AFFECTATION;}
        
        Affectation(string symbol)
            : symbol(symbol), value(nullptr) {type=AFFECTATION;} 

        Affectation(string symbol, shared_ptr<Node> value)
            : symbol(symbol), value(value) {type=AFFECTATION;}
        
        inline void setSymbol(string symbol_) override {symbol = symbol_;}
        inline string& getSymbol() override { return symbol; }
        inline shared_ptr<Node> getValue() override { return value; }
        void setValue(shared_ptr<Node> value) override { this->value = value; }
        virtual std::string toString() override;

    private:

        string symbol;
        shared_ptr<Node> value;

};