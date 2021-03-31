#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <list>
using namespace std;

class Block : public Instruction{

    public:
        Block( shared_ptr<Scope> scope, list<shared_ptr<Instruction>> instr) 
         : instructions(instr), scope(scope) {}

        virtual ~Block() {}

        inline shared_ptr<Scope> getScope() { return scope; }
        inline list<shared_ptr<Instruction>> getInstructions() { return instructions; }
        void toString(int n);
    private:
        list<shared_ptr<Instruction>> instructions;
        shared_ptr<Scope> scope;

};
