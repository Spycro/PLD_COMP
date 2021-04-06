#pragma once

#include "Type.h"
namespace VarType
{
    class Void : public Type {
        public :

        int getSize() override {
            return 0;
        }

        virtual std::string toString() override { return "Void"; }
        
    };
}
extern VarType::Void VOIDTYPE;