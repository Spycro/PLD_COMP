#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <list>
using namespace std;

class Block : public Instruction{

    public:
        inline Scope getScope() { return scope; }
        inline list<shared_ptr<Instruction>> getInstructions() { return instructions; }
        void toString(int n);
        inline bool isBlock() {return true; } override;
    private:
        list<shared_ptr<Instruction>> instructions;
        Scope scope;

};
