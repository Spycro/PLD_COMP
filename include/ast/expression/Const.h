#pragma once

#include "Expression.h"

class Const : public Expression
{

    public:
        Const() : value(0) {}

        Const(int value) : value(value) {}

        inline int getValue() { return value; }
        void setValue(int value) override { this->value = value; }
        virtual std::string toString() override;

    private:
        int value;

};