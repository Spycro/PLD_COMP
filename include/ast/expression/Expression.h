#pragma once

#include "../Instruction.h"

class Expression : public Instruction {

    public:
        
        Expression() {}

        virtual void setValue(int value) {}
        virtual void setValue(shared_ptr<Expression> value) {}
        virtual std::string toString() override;

    private:

};
