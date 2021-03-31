#pragma once
#include "Node.h"

class Instruction : public Node{

    public:
        virtual void toString(int n);
        Instruction() { }
    private:

};
