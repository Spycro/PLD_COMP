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

typedef enum
{
    PREINCR,
    POSTINCR,
    PREDECR,
    POSTDECR,
    PARENTHESIS,
    TILD,
    NOT
} UnaryOperator;


class Expression : public Instruction {

    public:
        
        Expression() {}
        virtual void setBinaryOperator(BinaryOperator) {}
        virtual void setOperand1(shared_ptr<Expression>) {}
        virtual void setOperand2(shared_ptr<Expression>) {}

        void setOperand(shared_ptr<Expression>) {}
        void setOp(UnaryOperator) {}

        void setSymbol(std::string) {} 

        virtual void setValue(int value) {}
        virtual void setValue(shared_ptr<Expression> value) {}
        virtual std::string toString() override;

    private:

};
