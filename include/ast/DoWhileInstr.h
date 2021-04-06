#pragma once

#include "ControlStructure.h"

class DoWhileInstr : public ControlStructure
{
    public:        
        DoWhileInstr() { type=DOWHILEINSTR; }

        virtual std::string toString() override;

    private:
};