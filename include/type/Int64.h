#pragma once

#include "Type.h"

namespace VarType
{
    class Int64 : public Type {
        public :

        int getSize() const override {
            return 8;
        }

        virtual std::string toString() override { return "Int"; }
        
    };
}
extern VarType::Int64 INTTYPE64;
