#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Array : public Expression
{

public:
    Array() 
        : position(nullptr) {type=ARRAY;}

    Array(string symbol, shared_ptr<Node> position) : symbol(symbol), position(position) {}


    inline string& getSymbol() override { return symbol; }
    inline shared_ptr<Node> getPosition() override { return position; }
    virtual std::string toString() override;

private:
    string symbol;
    shared_ptr<Node> position;
};