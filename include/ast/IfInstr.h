#pragma once

#include "ControlStructure.h"
#include <memory>
using namespace std;

class IfInstr : public ControlStructure {

    public:
        inline shared_ptr<Instruction> getCodeElse() { return codeElse; }
    private:
        shared_ptr<Instruction> codeElse;

};