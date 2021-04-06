#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <vector>

using namespace std;

class Block : public Instruction
{
    public:
        Block() 
        : scope(nullptr) {}

        Block(shared_ptr<Scope> scope) 
            : scope(move(scope)) {}
        Block( shared_ptr<Scope> scope, vector<shared_ptr<Instruction>> instr) 
         : instructions(instr), scope(scope) {}

        inline shared_ptr<Scope> getScope() { return scope; }
        inline vector<shared_ptr<Instruction>>& getInstructions() { return instructions; }

        void setScope(shared_ptr<Scope> s) { scope = s; }

        virtual std::string toString() override;
        inline bool isBlock() override { return true; }
    private:
        vector<shared_ptr<Instruction>> instructions;
        shared_ptr<Scope> scope;
};
