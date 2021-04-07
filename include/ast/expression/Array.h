#pragma once

#include "Expression.h"
#include "Variable.h"
#include <string>

using namespace std;

class Array : public Variable
{

public:
    Array() 
        : position(nullptr) {type=ARRAY;}

    Array(string symbol, shared_ptr<Node> position) : Variable(symbol), position(position) {type=ARRAY;}


    inline shared_ptr<Node> getPosition() override { return position; }
    inline void setPosition(shared_ptr<Node> position) override { this->position = position; }

    virtual std::string toString() override;

private:
    shared_ptr<Node> position;
};