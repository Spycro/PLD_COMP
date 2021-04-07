#pragma once

#include "Type.h"

namespace VarType
{
    class Char : public VarType::Type {
        public :

        int getSize() const override {
            return 1;
        }

        virtual std::string toString() override { return "Char"; }

    };
}
