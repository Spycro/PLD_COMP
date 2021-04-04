#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Array : public Expression
{

public:
    Array() 
        : position(nullptr) {}

    Array(string symbol, shared_ptr<Expression> position) : symbol(symbol), position(position) {}


    inline string& getSymbol() { return symbol; }
    inline shared_ptr<Expression> getPosition() { return position; }
    virtual std::string toString() override;

private:
    string symbol;
    shared_ptr<Expression> position;
};