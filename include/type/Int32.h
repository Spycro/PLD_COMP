#pragma once

#include "Type.h"
namespace VarType
{
    class Int32 : public Type {
        public :

        int getSize() const override {
            return 4;
        }

        virtual std::string toString() override { return "Int"; }
        
    };
}
extern VarType::Int32 INTTYPE32;