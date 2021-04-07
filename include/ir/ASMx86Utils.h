#pragma once

#include "SymbolTableElement.h"

namespace ASMx86Utils {

    char symbolSizeChar(int s);

    std::string moveTo64Reg(SymbolTableElement& s, SymbolTableElement& reg64);

    SymbolTableElement& getSubReg(SymbolTableElement& reg64, int s);

}