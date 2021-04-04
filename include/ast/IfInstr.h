#pragma once

#include "ControlStructure.h"
#include <memory>
using namespace std;

class IfInstr : public ControlStructure
{
    public:
        IfInstr() 
            : codeElse(nullptr) {}

        IfInstr( shared_ptr<Instruction> codeElse ) 
            : codeElse(codeElse) { }

        inline shared_ptr<Instruction>& getCodeElse() { return codeElse; }
        virtual std::string toString() override;
    private:
        shared_ptr<Instruction> codeElse;
};