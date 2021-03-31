#pragma once

#include "Expression.h"

class Const : public Expression
{

    public:
        virtual std::string toString() override;
        inline void setValue(int value) { this->value = value; }
    private:
        int value;

};