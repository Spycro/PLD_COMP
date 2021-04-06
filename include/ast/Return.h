#pragma once
#include "Instruction.h"
#include "expression/Expression.h"

#include <memory>

using namespace std;

class Return : public Instruction
{
    public:
        Return() : value(nullptr) { type=RETURN; }

        Return(shared_ptr<Node> value) : value(value) { }

        shared_ptr<Node> getValue() override { return value; }
        inline void setValue(shared_ptr<Node> value) override { this->value = value; }
        virtual std::string toString() override;
    private:
        shared_ptr<Node> value;

};