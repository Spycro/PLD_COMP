#pragma once

#include "Expression.h"

class Const : public Expression
{

    public:
        Const() : value(0) {}

        Const(int value) : value(value) {}

        inline int getValue() { return value; }
        inline void setValue(int value) { this->value = value; }
        virtual std::string toString() override;

    private:
        int value;

};