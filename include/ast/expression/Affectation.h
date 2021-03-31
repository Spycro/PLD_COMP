#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression
{

    public:
        Affectation() {}
        Affectation(string symbol, shared_ptr<Expression> value) : symbol(symbol), value(value) {}
        
        inline string& getSymbol() { return symbol; }
        inline shared_ptr<Expression> getValue() { return value; }
        inline void setValue(shared_ptr<Expression> value) { this->value = value; }
        virtual std::string toString() override;

    private:

        string symbol;
        shared_ptr<Expression> value;

};