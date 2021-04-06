#pragma once

#include "Expression.h"

class Const : public Expression
{

    public:
        Const() : constValue(0) {type=CONST;}

        Const(int value) : constValue(value) {}

        inline int getConstValue() override { return constValue; }
        void setConstValue(int value) override { this->constValue = value; }
        virtual std::string toString() override;

    private:
        int constValue;

};