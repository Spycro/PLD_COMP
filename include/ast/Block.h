#pragma once
#include "Instruction.h"
#include "Scope.h"
#include <list>
using namespace std;

class Block : public Instruction{

    public:

    private:
        list<shared_ptr<Instruction>> instructions;
        Scope scope;

};
