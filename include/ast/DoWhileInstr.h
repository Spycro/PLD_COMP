#pragma once

#include "ControlStructure.h"

class DoWhileInstr : public ControlStructure
{
    public:        
        DoWhileInstr() { }

        virtual std::string toString() override;

    private:
};