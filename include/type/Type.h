#pragma once
#include <string>

namespace VarType
{
    class Type {
        public :

        virtual int getSize() = 0;

        virtual std::string toString() = 0;
    };
}
