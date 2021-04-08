#pragma once
#include <string>

namespace VarType
{
    class Type {
        public :

        virtual int getSize() const = 0;

        virtual std::string toString() = 0;

        inline const Type* getLargestType(const Type* otherType) const{return (getSize()<otherType->getSize())?otherType:this;}

    };
}
