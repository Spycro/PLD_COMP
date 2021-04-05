#pragma once

#include "Type.h"

namespace VarType
{
    class Char : public VarType::Type {
        public :

        int getSize() override {
            return 4;
        }

        virtual std::string toString() override { return "Char"; }

    };
}
