#pragma once
#include "Instruction.h"
#include "Return.h"

#include <list>
#include <map>

using namespace std;

class Function {

    public:

    private:

        list<Instruction> Instructions;
        map<string, string> ListeSymboles;
        Return ReturnStatement;

};
