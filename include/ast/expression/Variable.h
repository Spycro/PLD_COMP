#pragma once

#include "Expression.h"
#include <string>
using namespace std;

// TODO : ajouter type

class Variable : public Expression {

    public:
        Variable() {type=VARIABLE;}

        Variable(string symbol) : symbol(symbol) {type=VARIABLE;}
        
        inline string& getSymbol() override { return symbol; }

        void setSymbol(std::string symb) override { symbol = symb; }

        virtual std::string toString() override;

    private:
        string symbol;
};