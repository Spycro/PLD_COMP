#pragma once
#include "../IRInstr.h"

class Copy : public IRInstr
{
    public:
        Copy(BasicBlock* bb, Type* t, std::string d, std::string x);

        void gen_asm(std::ostream &o) override;
    
    private:
        std::string d, x;

};

