#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <vector>
using namespace std;

class Block : public Instruction{

    public:
        inline Scope& getScope() { return scope; }
        inline vector<shared_ptr<Instruction>>& getInstructions() { return instructions; }
        void toString(int n);
        inline bool isBlock() { return true; }
        
    private:
        vector<shared_ptr<Instruction>> instructions;
        Scope scope;

};
