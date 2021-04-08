#pragma once

#include "Type.h"
#include "Int64.h"
#include "Char.h"

namespace VarType
{
    inline VarType::Type* getType(std::string typeName) {
        if (typeName == "int") {
            return new VarType::Int64();
        } else if (typeName == "char") {
            return new VarType::Char();
        } else if (typeName == "void") {
            return new VarType::Void();
        }

        // unrecognised type
        std::cerr<<"__PRETTY_FUNCTION__ : unrecognised type (" + typeName + ")"<<endl;
        throw;
    }
}
