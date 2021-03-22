#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <iostream>
#include <list>
using namespace std;

class Block : public Instruction{

    public:
        inline Scope getScope() { return scope; }
        inline list<shared_ptr<Instruction>> getInstructions() { return instructions; }
        void toString(int n);
    private:
        list<shared_ptr<Instruction>> instructions;
        Scope scope;

};
