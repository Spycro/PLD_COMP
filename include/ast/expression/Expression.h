#pragma once

#include "../Instruction.h"

typedef enum
{
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    EQUAL,
    NE,
    GTE,
    LTE,
    GT,
    LT,
    BINAND,
    LOGAND,
    BINOR,
    LOGOR,
    BINXOR,
    LOGXOR
} BinaryOperator;


class Expression : public Instruction {

    public:
        
        Expression() {}
        virtual void setBinaryOperator(BinaryOperator) {}
        virtual void setOperand1(shared_ptr<Expression>) {}
        virtual void setOperand2(shared_ptr<Expression>) {}
        virtual void setValue(int value) {}
        virtual void setValue(shared_ptr<Expression> value) {}
        virtual std::string toString() override;

    private:

};
