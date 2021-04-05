#pragma once

#include "Type.h"
#include "Int.h"
#include "Char.h"

namespace VarType
{
    inline VarType::Type* getType(std::string typeName) {
        if (typeName == "int") {
            return new VarType::Int();
        } else if (typeName == "char") {
            return new VarType::Char();
        }

        // unrecognised type
        std::cerr<<"__PRETTY_FUNCTION__ : unrecognised type (" + typeName + ")"<<endl;
        throw;
    }
}
