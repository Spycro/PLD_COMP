#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <vector>

using namespace std;

class Block : public Instruction
{
    public:
        Block() 
        : scope(nullptr) { type=BLOCK; }

        Block(shared_ptr<Scope> scope) 
            : scope(move(scope)) {}
        Block( shared_ptr<Scope> scope, vector<shared_ptr<Node>> instr) 
         : instructions(instr), scope(scope) {}

        inline shared_ptr<Scope> getScope() override { return scope; }
        inline vector<shared_ptr<Node>>& getInstructions() override { return instructions; }

        void setScope(shared_ptr<Scope> s) override { scope = s; }

        virtual std::string toString() override;
    private:
        vector<shared_ptr<Node>> instructions;
        shared_ptr<Scope> scope;

};
