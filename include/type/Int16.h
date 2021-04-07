#pragma once

#include "Type.h"

namespace VarType
{
    class Int16 : public Type {
        public :

        int getSize() const override {
            return 2;
        }

        virtual std::string toString() override { return "Int16"; }
        
    };
}

extern VarType::Int16 INTTYPE16;