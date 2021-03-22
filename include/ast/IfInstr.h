#pragma once

#include "ControlStructure.h"

using namespace std;

class IfInstr : public ControlStructure {

    public:

    private:
        shared_ptr<Instruction> codeElse;

};