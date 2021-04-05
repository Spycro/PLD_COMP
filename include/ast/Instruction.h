#pragma once
#include "Node.h"

class Instruction : public Node
{
    public:
        Instruction() { }

        virtual std::string toString() override;

    private:
};
