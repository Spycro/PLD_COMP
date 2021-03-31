#pragma once

#include "Expression.h"

class Const : public Expression {

    public:
        Const(int value) : value(value) {}

        inline int getValue() { return value; }
        void toString(int n);

    private:
        int value;

};