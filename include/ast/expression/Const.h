#pragma once

#include "Expression.h"

class Const : public Expression {

    public:
        void toString(int n);
        Const(int value) : value(value) {}

        int getValue() { return value; }
    private:
        int value;

};