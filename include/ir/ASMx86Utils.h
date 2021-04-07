#pragma once

#include "SymbolTableElement.h"

namespace ASMx86Utils {

    char symbolSizeChar(int s);

    /**
     * Move one value from a given symbol into another.
     * 
     * Sign-extend the value if dst.getSize() > src.getSize().
     * Uses registry to perform the sign-extend before moving the value back into dst.
     */
    std::string moveTo(SymbolTableElement& src, SymbolTableElement& dst);

    //TODO: remove, use moveTo instead, to test before removing
    std::string moveTo64Reg(SymbolTableElement& s, SymbolTableElement& reg64);

    SymbolTableElement& getSubReg(SymbolTableElement& reg64, int s);

}