#pragma once

#include "ControlStructure.h"

class WhileInstr : public ControlStructure {

    public:
        WhileInstr() { type=WHILEINSTR;}

        virtual std::string toString() override;

    private:

};