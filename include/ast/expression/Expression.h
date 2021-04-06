#pragma once

#include "../Instruction.h"




class Expression : public Instruction {

    public:
        
        Expression() {}
        virtual std::string toString() override;

    private:

};
