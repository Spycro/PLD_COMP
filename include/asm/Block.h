#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <list>
using namespace std;

class Block : public Instruction{

    public:

    private:
        list<Instruction> instructions;
        Scope scope;

};
