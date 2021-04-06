#pragma once

#include "ControlStructure.h"
#include <memory>
using namespace std;

class IfInstr : public ControlStructure
{
    public:
        IfInstr() 
            : codeElse(nullptr) { type=INFINSTR; }

        IfInstr( shared_ptr<Node> codeElse ) 
            : codeElse(codeElse) { }

        inline shared_ptr<Node> getCodeElse() override { return codeElse; }
        inline void setCodeElse(shared_ptr<Node> codeElse) override { this->codeElse = codeElse; } 

        virtual std::string toString() override;
    private:
        shared_ptr<Node> codeElse;
};